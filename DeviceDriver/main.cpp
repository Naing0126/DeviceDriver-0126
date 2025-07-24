#include "gmock/gmock.h"
#include "device_driver.h"

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));

private:
	unsigned char data = 0;
};

TEST(DeviceDriver, ReadFromHW) {
	MockFlashMemoryDevice mock;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read(0xB);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}