#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int ret = getDataFromHW(address);
    for (int i = 0; i < 4; i++) {
        if (ret != getDataFromHW(address)) throw ReadFailException();
    }
    return ret;
}

int DeviceDriver::getDataFromHW(long address)
{
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}