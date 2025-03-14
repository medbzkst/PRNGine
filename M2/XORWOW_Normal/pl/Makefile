PLATFORM := xilinx_vck5000_gen4x8_xdma_2_202210_1
TARGET := hw
FREQ := 250

XSA = $(strip $(patsubst %.xpfm, % , $(shell basename $(PLATFORM))))

BUILD_DIR = build.$(TARGET)
VPP_FLAGS = -t $(TARGET) --platform $(PLATFORM)# --save-temps
VPP_FLAGS += --kernel_frequency $(FREQ)

all: $(BUILD_DIR)/pl_mm2s_40x.xo $(BUILD_DIR)/pl_s2mm_40x.xo

$(BUILD_DIR)/pl_mm2s_40x.xo: pl_mm2s_40x.cpp
	v++ $(VPP_FLAGS) -k $(subst $(BUILD_DIR)/,,$(subst .xo,,$@)) -c -g -o $@ $^

$(BUILD_DIR)/pl_s2mm_40x.xo: pl_s2mm_40x.cpp
	v++ $(VPP_FLAGS) -k $(subst $(BUILD_DIR)/,,$(subst .xo,,$@)) -c -g -o $@ $^

clean:
	rm -rf $(BUILD_DIR) *.log *.jou .Xil/ _x/