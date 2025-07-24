#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;
using namespace std;

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
TEST(DeviceDriver, NotSameResponse) {
	MockFlashMemoryDevice mock;

	EXPECT_CALL(mock, read((long)0xB))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0));

	try {
		DeviceDriver driver{ &mock };
		int data = driver.read(0xB);
		FAIL();
	}
	catch (const exception& e) {
		EXPECT_EQ(string{ e.what() }, string{ READ_FAIL_MESSAGE });
	}
}
TEST(DeviceDriver, AllSameResponse) {
	MockFlashMemoryDevice mock;
	int expect = 0;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(5)
		.WillRepeatedly(Return(expect));

	DeviceDriver driver{ &mock };
	EXPECT_THAT(driver.read(0xB), Eq(expect));
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}