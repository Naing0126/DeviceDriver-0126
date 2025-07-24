#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;
using namespace std;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
protected:
	MockFlashMemoryDevice mock;
	DeviceDriver driver{ &mock };
};

TEST_F(DeviceDriverFixture, CheckReadFromHW5times) {
	EXPECT_CALL(mock, read((long)0xB))
		.Times(5);

	int data = driver.read(0xB);
}
TEST_F(DeviceDriverFixture, NotSameResponseForRead) {
	EXPECT_CALL(mock, read((long)0xB))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0));

	try {
		int data = driver.read(0xB);
		FAIL();
	}
	catch (const exception& e) {
		EXPECT_EQ(string{ e.what() }, string{ READ_FAIL_MESSAGE });
	}
}
TEST_F(DeviceDriverFixture, AllSameResponseForRead) {
	int expect = 0;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(5)
		.WillRepeatedly(Return(expect));

	EXPECT_THAT(driver.read(0xB), Eq(expect));
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}