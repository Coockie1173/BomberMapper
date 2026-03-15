#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "World.h"
#include "../macros.h"

unsigned char MapLoaded = 0;
Layerfile* LoadedLayerFile;
int WallDataSize = 0;
WallData* MapWallData;

uint32_t bswap32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

const vec3 TileColours[0xF] = 
{
    {0,0,0},
    {1,0.69f,0},
    {0, 1, 0.086f},
    {0,0,1},
    {0,0,1},
    {0,0,1},
    {0,0,1},
    {0.349f,1,1},
    {0.349f,1,1},
    {1,0,0},
    {0, 1, 0.086f},
    {0, 1, 0.086f},
    {0.349f,1,1},
    {0.349f,1,1},
    {0,0,0},
    {0,0,0}
};

void UnloadMap(Layerfile* LoadedFile)
{
    // Iterate over each section and free memory for SubSections and their data
    for (int i = 0; i < LoadedFile->SectionCount; i++) {
        Section* section = LoadedFile->Sections[i];
        if (section) {
            // Free each SubSection's data
            for (int j = 0; j < section->AmmSubsections; j++) {
                SubSection* subSection = section->SubSections[j];
                if (subSection) {
                    free(subSection->Data); // Free the Data array
                    free(subSection); // Free the SubSection
                }
            }
            // Free the SubSections array
            free(section->SubSections);
            free(section); // Free the Section
        }
    }
    
    // Free the Sections array
    free(LoadedFile->Sections);
    
    // Free the Layerfile itself
    free(LoadedFile);
}

void LoadBin(const char* FilePath, Layerfile** LoadedFile)
{
    FILE* file = fopen(FilePath, "rb");
    if (!file) {
        return;
    }
    
    fseek(file, 0, SEEK_END);
    size_t dataSize = ftell(file);
    rewind(file);
    
    uint8_t* RawData = (uint8_t*)malloc(dataSize);
    if (!RawData) {
        fclose(file);
        return;
    }
    
    fread(RawData, 1, dataSize, file);
    fclose(file);
    
    if (!RawData || dataSize < 2) {
        free(RawData);
        return;
    }
    
    *LoadedFile = (Layerfile*)malloc(sizeof(Layerfile));
    if (!*LoadedFile) {
        free(RawData);
        return;
    }
    
    (*LoadedFile)->Header = *(uint32_t*)RawData;
    (*LoadedFile)->Header = bswap32((*LoadedFile)->Header);
    (*LoadedFile)->DeathOffset = RawData[4];
    
    uint8_t AmmSections = RawData[0];
    (*LoadedFile)->SectionCount = RawData[0];
    
    (*LoadedFile)->Sections = (Section**)malloc(AmmSections * sizeof(Section*));
    if (!(*LoadedFile)->Sections) {
        free(*LoadedFile);
        free(RawData);
        return;
    }
    
    size_t offset = 5;
    for (int ParsedSections = 0; ParsedSections < AmmSections; ParsedSections++) {
        if (offset + 3 > dataSize) {
            break;
        }
        
        Section* Cursec = (Section*)malloc(sizeof(Section));
        if (!Cursec) {
            break;
        }
        
        Cursec->AmmPartsInSubsections = RawData[offset++];
        Cursec->AmmSubsections = RawData[offset++];
        Cursec->HeightOffset = RawData[offset++];
        Cursec->SubsectionLength = 0x80;
        
        int numSubsections = 0xC00 / Cursec->SubsectionLength;
        Cursec->AmmSubsections = numSubsections = 0xC00 / Cursec->SubsectionLength;
        Cursec->SubSections = (SubSection**)malloc(numSubsections * sizeof(SubSection*));
        if (!Cursec->SubSections) {
            free(Cursec);
            break;
        }
        
        for (int S = 0; S < numSubsections; S++) {
            if (offset + 2 > dataSize) {
                break;
            }
            
            SubSection* s = (SubSection*)malloc(sizeof(SubSection));
            if (!s) {
                break;
            }
            
            s->HeaderbyteOne = RawData[offset++];
            s->HeaderbyteTwo = RawData[offset++];
            s->Data = (uint16_t*)malloc(Cursec->SubsectionLength / 2 * sizeof(uint16_t));
            if (!s->Data) {
                free(s);
                break;
            }
            
            for (int i = 0; i < Cursec->SubsectionLength / 2; i++) {
                if (offset + 2 > dataSize) {
                    break;
                }
                uint16_t value = (RawData[offset] << 8) | RawData[offset + 1];
                s->Data[i] = value;
                offset += 2;
            }
            Cursec->SubSections[S] = s;
        }
        (*LoadedFile)->Sections[ParsedSections] = Cursec;
    }
    
    free(RawData);
}

void CalculateWalls(Layerfile* LoadedFile)
{
    if(MapWallData != NULL)
    {
        free(MapWallData);
    }

    MapWallData = malloc(0);

    uint16_t*** OrderedData = malloc(sizeof(uint16_t**) * LoadedLayerFile->SectionCount);

    for(int SectionID = 0; SectionID < LoadedLayerFile->SectionCount; SectionID++)
    {
        for(int SubsectionID = 0; SubsectionID < LoadedLayerFile->Sections[SectionID]->AmmSubsections; SubsectionID++)
        {
            for(int y = 0; y < 8; y++)
            {
                for(int x = 0; x < 8; x++)
                {

                }
            }
        }

    }
}