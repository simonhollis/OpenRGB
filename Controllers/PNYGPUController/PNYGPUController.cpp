/*-----------------------------------------*\
|  PNYGPUController.cpp                     |
|                                           |
|  Driver for PNY GPU RGB (Turing)          |
|  lighting controller                      |
|                                           |
|  KendallMorgan   10/17/2021               |
\*-----------------------------------------*/

#include "PNYGPUController.h"

PNYGPUController::PNYGPUController(i2c_smbus_interface* bus, pny_dev_id dev)
{
    this->bus = bus;
    this->dev = dev;
}

PNYGPUController::~PNYGPUController()
{

}

std::string PNYGPUController::GetDeviceLocation()
{
    std::string return_string(bus->device_name);
    char addr[5];
    snprintf(addr, 5, "0x%02X", dev);
    return_string.append(", address ");
    return_string.append(addr);
    return("I2C: " + return_string);
}

void PNYGPUController::WriteI2CData(u8 command, u8 length, u8* data)
{
    //Simulating i2c_smbus_write_i2c_block_data(command, length, data);
    for (u8 i = 0; i < length; i++)
    {
        bus->i2c_smbus_write_byte_data(dev, command+i, data[i]);
    }
}

unsigned char PNYGPUController::GetMode()
{
    return(bus->i2c_smbus_read_byte_data(dev, PNY_GPU_MODE_OFF));
}

unsigned char PNYGPUController::GetRed()
{
    return(bus->i2c_smbus_read_byte_data(dev, PNY_GPU_REG_COLOR_RED));
}

unsigned char PNYGPUController::GetGreen()
{
    return(bus->i2c_smbus_read_byte_data(dev, PNY_GPU_REG_COLOR_GREEN));
}

unsigned char PNYGPUController::GetBlue()
{
    return(bus->i2c_smbus_read_byte_data(dev, PNY_GPU_REG_COLOR_BLUE));
}

void PNYGPUController::SetOff()
{
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_CONTROL,                0);
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_MODE,                   0x00);
}

void PNYGPUController::SetCycle(unsigned char speed)
{
    // u8 loop[] = {
    //     0x01,  // Direction
    //     0x00,  // ??
    //     speed, // Speed
    //     0x1F   // Somehow related to speed
    // };
    // loop[2] = speed;
    u8 seq1[] = {  // 0x82 mode register e.g. off = all 0s
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };
    u8 seq2[] = {
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };
    u8 seq3[] = {
        0x01,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };
    u8 seq4[] = {
        0x02,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };
    u8 seq5[] = {  // 0x02 color register e.g. off is all-zeros
        0x03,
        0xff,
        0x00,
        0x00,
        0xaa,
        0x00,
        0x00
    };
    u8 seq6[] = {  // 0x03 always same - 'commit'?
        0x11,
        0x33,
        0x55,
        0x77,
        0xaa,
        0xcc,
        0xee
    };

    WriteI2CData(0x82, sizeof(seq1), seq1);
    WriteI2CData(0x83, sizeof(seq2), seq2);
    WriteI2CData(0x83, sizeof(seq3), seq3);
    WriteI2CData(0x83, sizeof(seq4), seq4);
    WriteI2CData(0x02, sizeof(seq5), seq5);
    WriteI2CData(0x03, sizeof(seq6), seq6);

}

void PNYGPUController::SetStrobe(unsigned char r, unsigned char g, unsigned char b, unsigned char speed, unsigned char brightness)
{
    u8 strobe[] = {
        0x02,       // Strobe
        0x00,       // Rise speed
        speed,      // Cycle length/2
        0x00,       // Off delay
        r,          // R
        g,          // G
        b,          // B
        brightness, // Peak brightness
        0x05        // Fade speed
    };
    WriteI2CData(PNY_GPU_REG_CONTROL, sizeof(strobe), strobe);
}

void PNYGPUController::SetDirect(unsigned char red, unsigned char green, unsigned char blue, unsigned char brightness)
{
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_CONTROL,                0);
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_MODE,                   0x01);
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_COLOR_RED,              red);
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_COLOR_BLUE,             blue);
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_COLOR_GREEN,            green);
    bus->i2c_smbus_write_byte_data(dev, PNY_GPU_REG_COLOR_BRIGHTNESS,       brightness);
}
