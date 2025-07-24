#include "gmock/gmock.h"
#include "device_driver.h"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	unsigned char read(long address) override {
		return 0;
	}
	void write(long address, unsigned char data) override {

	}

};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMemoryDevice* hardware = new MockFlashMemoryDevice;
	DeviceDriver driver{ hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}