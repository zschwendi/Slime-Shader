import AppKit
import Combine
import CoreGraphics
import Foundation
import SwiftUI

private final class NativeRenderer {
    let pointer: OpaquePointer

    init?(height: Int, width: Int, density: Double, speed: Double) {
        guard let pointer = slime_renderer_create(Int32(height), Int32(width), density, speed) else {
            return nil
        }
        self.pointer = pointer
    }

    deinit {
        slime_renderer_destroy(pointer)
    }
}

@MainActor
private final class PreviewModel: ObservableObject {
    let width = 320
    let height = 180
    @Published private(set) var image: CGImage?
    @Published private(set) var elapsedSeconds = 0.0
    @Published private(set) var frameCount = 0
    @Published private(set) var error: String?

    private let renderer: NativeRenderer?
    private var pixels: [UInt8]
    private var startedAt: Double?

    init() {
        renderer = NativeRenderer(height: height, width: width, density: 4.0, speed: 0.25)
        pixels = Array(repeating: 0, count: width * height * 4)
        if renderer == nil {
            error = "Could not create the C++ renderer."
        }
    }

    func start() {
        startedAt = ProcessInfo.processInfo.systemUptime
        update()
    }

    func update() {
        guard let renderer, let startedAt else { return }
        let seconds = ProcessInfo.processInfo.systemUptime - startedAt
        let copied = pixels.withUnsafeMutableBufferPointer { buffer in
            slime_renderer_copy_rgba(renderer.pointer, seconds, buffer.baseAddress, buffer.count)
        }
        guard copied else {
            error = "The C++ renderer could not supply a frame."
            return
        }

        // The image provider retains an owned snapshot after this update returns.
        let data = Data(pixels) as CFData
        guard let provider = CGDataProvider(data: data),
              let colorSpace = CGColorSpace(name: CGColorSpace.sRGB),
              let frame = CGImage(
                width: width, height: height, bitsPerComponent: 8, bitsPerPixel: 32,
                bytesPerRow: width * 4, space: colorSpace,
                bitmapInfo: CGBitmapInfo.byteOrder32Big.union(
                    CGBitmapInfo(rawValue: CGImageAlphaInfo.premultipliedLast.rawValue)),
                provider: provider, decode: nil, shouldInterpolate: false,
                intent: .defaultIntent
              ) else {
            error = "Could not display the C++ pixel buffer."
            return
        }
        image = frame
        elapsedSeconds = seconds
        frameCount += 1
        error = nil
    }
}

@MainActor
private struct PreviewView: View {
    @StateObject private var model = PreviewModel()
    private let ticks = Timer.publish(every: 1.0 / 30.0, on: .main, in: .common).autoconnect()

    var body: some View {
        VStack(spacing: 10) {
            ZStack {
                Color.black
                if let image = model.image {
                    Image(decorative: image, scale: 1)
                        .resizable()
                        .interpolation(.none)
                }
            }
            .frame(width: 960, height: 540)
            .accessibilityLabel("Live C++ shader output")

            HStack {
                Text("C++ frame \(model.frameCount)")
                Spacer()
                Text(String(format: "%.2f seconds", model.elapsedSeconds))
            }
            .font(.system(.caption, design: .monospaced))

            if let error = model.error {
                Text(error).foregroundStyle(.red)
            } else {
                Text("Every frame comes from SlimeShader::RainbowWave(seconds).")
                    .font(.caption)
                    .foregroundStyle(.secondary)
            }
        }
        .padding(12)
        .onAppear { model.start() }
        .onReceive(ticks) { _ in model.update() }
    }
}

@MainActor
private final class PreviewAppDelegate: NSObject, NSApplicationDelegate {
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
        true
    }
}

@main
private struct SlimePreviewApp: App {
    @NSApplicationDelegateAdaptor(PreviewAppDelegate.self) private var delegate

    var body: some Scene {
        WindowGroup("SlimeShader Preview") {
            PreviewView()
        }
        .windowResizability(.contentSize)
    }
}
