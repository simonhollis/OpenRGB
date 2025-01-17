/*-----------------------------------------*\
|  PNYGPUController.h                       |
|                                           |
|  Definitions and types for PNY GPU RGB    |
|  (Turing) lighting controller             |
|                                           |
|  KendallMorgan   10/17/2021               |
\*-----------------------------------------*/

#include <string>
#include "i2c_smbus.h"

#pragma once

typedef unsigned char   pny_dev_id;

enum
{
    PNY_GPU_REG_CONTROL                 = 0xE0,
    PNY_GPU_REG_MODE                    = 0x60,
    PNY_GPU_REG_COLOR_RED               = 0x6C,
    PNY_GPU_REG_COLOR_GREEN             = 0x6D,
    PNY_GPU_REG_COLOR_BLUE              = 0x6E,
    PNY_GPU_REG_COLOR_BRIGHTNESS        = 0x6F,
    PNY_ADA_GPU_REG_CONTROL                 = 0x82,
    PNY_ADA_GPU_REG_MODE                    = 0x83,
    PNY_ADA_GPU_REG_COLOR_RED               = 0x6C,
    PNY_ADA_GPU_REG_COLOR_GREEN             = 0x6D,
    PNY_ADA_GPU_REG_COLOR_BLUE              = 0x6E,
    PNY_ADA_GPU_REG_COLOR_BRIGHTNESS        = 0x6F,
};

enum
{
    PNY_GPU_MODE_OFF                    = 0x00,
    PNY_GPU_MODE_DIRECT                 = 0x01,
    PNY_GPU_MODE_CYCLE                  = 0x02,
    PNY_GPU_MODE_STROBE                 = 0x03,
};

class PNYGPUController
{
public:
	PNYGPUController(i2c_smbus_interface* bus, pny_dev_id dev);
	~PNYGPUController();

	std::string     GetDeviceLocation();

    void SetOff();
    void SetCycle(unsigned char speed);
    void SetStrobe(unsigned char r, unsigned char g, unsigned char b, unsigned char speed, unsigned char brightness);
    void SetDirect(unsigned char red, unsigned char green, unsigned char blue, unsigned char brightness);

private:
	i2c_smbus_interface*    bus;
	pny_dev_id              dev;

    void            WriteI2CData(u8 command, u8 length, u8* data);
    unsigned char   GetMode();
    unsigned char   GetRed();
    unsigned char   GetGreen();
    unsigned char   GetBlue();

};
