CXX := clang++
SWIFTC := xcrun swiftc
CPPFLAGS := -I.
MACOS_MIN := 13.0
CXXFLAGS := -std=c++11 -O2 -Wall -Wextra -MMD -MP -mmacosx-version-min=$(MACOS_MIN)
ARCH := $(shell uname -m)

BUILD_DIR := .build
APP := $(BUILD_DIR)/SlimePreview.app
PREVIEW := $(APP)/Contents/MacOS/SlimePreview
SOURCES := Image.cpp Slime_Shader.cpp Preview/SlimeBridge.cpp
OBJECTS := $(addprefix $(BUILD_DIR)/obj/,$(SOURCES:.cpp=.o))

.PHONY: all preview clean

all: $(PREVIEW)

preview: $(PREVIEW)
	open "$(APP)"

$(PREVIEW): $(OBJECTS) Preview/SlimePreview.swift Preview/SlimeBridge.h Preview/Info.plist
	mkdir -p "$(@D)"
	cp Preview/Info.plist "$(APP)/Contents/Info.plist"
	$(SWIFTC) -swift-version 6 -parse-as-library -O \
		-target $(ARCH)-apple-macos$(MACOS_MIN) \
		-import-objc-header Preview/SlimeBridge.h \
		Preview/SlimePreview.swift $(OBJECTS) -lc++ \
		-framework SwiftUI -framework AppKit -framework CoreGraphics -o "$@"

$(BUILD_DIR)/obj/%.o: %.cpp Makefile
	mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c "$<" -o "$@"

clean:
	rm -rf "$(BUILD_DIR)"

-include $(OBJECTS:.o=.d)
