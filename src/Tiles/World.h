#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdint.h>
#define SECTIONSIZE 8

#define SECTION_HEADSIZE 0x2
#define LAYER_HEADSIZE 0x3
#define MAP_HEADSIZE 0x5
#define TILE_MEMSIZE 0x2
#define SECTION_MEMSIZE SECTION_HEADSIZE + ((SECTIONSIZE * SECTIONSIZE) * TILE_MEMSIZE)

enum CollisionType
{
    AIR,
    FLOOR,
    EFFECT_1,
    RAMP_D,
    RAMP_U,
    RAMP_R,
    RAMP_L,
    WALL_C_UL,
    WALL_C_DL,
    KILL,
    EFFECT_2,
    EFFECT_3,
    WALL_C_UR,
    WALL_C_DR,
    UNK_E,
    WALL
};

struct Tile
{
    uint8_t Byte1;
    uint8_t Byte2;
};

struct SubSection
{
    uint8_t HeaderbyteOne;
    uint8_t HeaderbyteTwo;
    struct Tile* Data;
};

struct Section
{
    struct SubSection* SubSections;
    uint8_t AmmSubsections;
    uint8_t AmmPartsInSubsections;
    uint8_t HeightOffset;
    int SubsectionLength;
    int SubsectionOffset;
};

struct LayerFile
{
    uint32_t Header;
    uint8_t DeathOffset;
    struct Section* Sections;
};

extern unsigned char MapLoaded;
extern struct LayerFile* LoadedFile;

void LoadBin(const char* FilePath);
void UnloadMap();

#endif