#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

#ifdef _MSC_VER
    #include <intrin.h>
    #define bswap16 _byteswap_ushort
#else
    #define bswap16 __builtin_bswap16
#endif

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

extern const vec3 TileColours[];

typedef struct {
    uint8_t HeaderbyteOne;
    uint8_t HeaderbyteTwo;
    uint16_t* Data;
} SubSection;

typedef struct {
    SubSection** SubSections;
    uint8_t AmmSubsections;
    uint8_t AmmPartsInSubsections;
    uint8_t HeightOffset;
    int SubsectionLength;
    int SubsectionOffset;
} Section;

typedef struct {
    uint8_t SectionCount;
    int Header;
    uint8_t DeathOffset;
    Section** Sections;
} Layerfile;


extern unsigned char MapLoaded;
extern Layerfile* LoadedLayerFile;

void LoadBin(const char* FilePath, Layerfile** LoadedFile);
void UnloadMap(Layerfile* LoadedFile);

#endif