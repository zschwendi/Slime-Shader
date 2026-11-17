CXX := clang++
SWIFTC := xcrun swiftc
CPPFLAGS := -I..
MACOS_MIN := 13.0
CXXFLAGS := -std=c++11 -O2 -Wall -Wextra -MMD -MP -mmacosx-version-min=$(MACOS_MIN)
ARCH := $(shell uname -m)

BUILD_DIR := .build
APP := $(BUILD_DIR)/SlimePreview.app
PREVIEW := $(APP)/Contents/MacOS/SlimePreview
OBJECTS := $(BUILD_DIR)/obj/Image.o $(BUILD_DIR)/obj/Slime_Shader.o $(BUILD_DIR)/obj/SlimeBridge.o

.PHONY: all run clean

all: $(PREVIEW)

run: $(PREVIEW)
	open "$(APP)"

$(PREVIEW): $(OBJECTS) SlimePreview.swift SlimeBridge.h Info.plist
	mkdir -p "$(@D)"
	cp Info.plist "$(APP)/Contents/Info.plist"
	$(SWIFTC) -swift-version 6 -parse-as-library -O \
		-target $(ARCH)-apple-macos$(MACOS_MIN) \
		-import-objc-header SlimeBridge.h \
		SlimePreview.swift $(OBJECTS) -lc++ \
		-framework SwiftUI -framework AppKit -framework CoreGraphics -o "$@"

$(BUILD_DIR)/obj/SlimeBridge.o: SlimeBridge.cpp Makefile
	mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c "$<" -o "$@"

$(BUILD_DIR)/obj/%.o: ../%.cpp Makefile
	mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c "$<" -o "$@"

clean:
	rm -rf "$(BUILD_DIR)"

-include $(OBJECTS:.o=.d)
