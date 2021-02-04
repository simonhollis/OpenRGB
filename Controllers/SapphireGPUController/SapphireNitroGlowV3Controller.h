/*-----------------------------------------*\
|  SapphireNitroGlowV3Controller.h          |
|                                           |
|  Definitions and types for Sapphire Nitro |
|  Glow V3 GPU RGB lighting controller      |
|                                           |
|  K900 2/3/2021                            |
\*-----------------------------------------*/

#include <string>
#include "i2c_smbus.h"

#pragma once

typedef unsigned char	sapphire_dev_id;

enum
{
    SAPPHIRE_NITRO_GLOW_V3_REG_MODE                             = 0x10,
    SAPPHIRE_NITRO_GLOW_V3_REG_EXTERNAL_CONTROL                 = 0x0F,
    SAPPHIRE_NITRO_GLOW_V3_REG_BRIGHTNESS                       = 0x3E,
    SAPPHIRE_NITRO_GLOW_V3_REG_RUNWAY_ANIMATION_SPEED           = 0x11,
    SAPPHIRE_NITRO_GLOW_V3_REG_RUNWAY_ANIMATION_REPEAT_COUNT    = 0x12,
    SAPPHIRE_NITRO_GLOW_V3_REG_COLOR_CYCLE_ANIMATION_SPEED      = 0x13,
    SAPPHIRE_NITRO_GLOW_V3_REG_RAINBOW_ANIMATION_SPEED          = 0x15,
    SAPPHIRE_NITRO_GLOW_V3_REG_SERIAL_ANIMATION_SPEED           = 0x16,
    SAPPHIRE_NITRO_GLOW_V3_REG_MUSIC_VOLUME                     = 0x29,
    SAPPHIRE_NITRO_GLOW_V3_REG_RED                              = 0x1A,
    SAPPHIRE_NITRO_GLOW_V3_REG_GREEN                            = 0x1B,
    SAPPHIRE_NITRO_GLOW_V3_REG_BLUE                             = 0x1C,
};

enum
{
    SAPPHIRE_NITRO_GLOW_V3_MODE_RAINBOW             = 0x00,
    SAPPHIRE_NITRO_GLOW_V3_MODE_RUNWAY              = 0x01,
    SAPPHIRE_NITRO_GLOW_V3_MODE_COLOR_CYCLE         = 0x02,
    SAPPHIRE_NITRO_GLOW_V3_MODE_SERIAL              = 0x03,
    SAPPHIRE_NITRO_GLOW_V3_MODE_SAPPHIRE_BLUE       = 0x04,
    SAPPHIRE_NITRO_GLOW_V3_MODE_AUDIO_VISUALIZATION = 0x05,
    SAPPHIRE_NITRO_GLOW_V3_MODE_CUSTOM              = 0x06,
    SAPPHIRE_NITRO_GLOW_V3_MODE_OFF                 = 0x07,
    SAPPHIRE_NITRO_GLOW_V3_MODE_EXTERNAL_CONTROL    = 0xFF,
};

class SapphireNitroGlowV3Controller
{
public:
    SapphireNitroGlowV3Controller(i2c_smbus_interface* bus, sapphire_dev_id dev);
    ~SapphireNitroGlowV3Controller();

    std::string     GetDeviceLocation();

    unsigned char   GetRed();
    unsigned char   GetGreen();
    unsigned char   GetBlue();

    void            SetColor(unsigned char red, unsigned char green, unsigned char blue);
    void            SetMode(unsigned char mode, unsigned char speed);

private:
    i2c_smbus_interface*    bus;
    sapphire_dev_id         dev;

};