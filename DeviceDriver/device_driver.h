#pragma once
#include <stdexcept>
#include "flash_memory_device.h"

const static char* READ_FAIL_MESSAGE = "ReadFailException!!!";

class ReadFailException : public std::exception {
public:
    char const* what() const override {
        return READ_FAIL_MESSAGE;
    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};