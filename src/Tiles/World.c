#include <stdio.h>
#include <stdlib.h>
#include "World.h"
#include "../macros.h"

unsigned char MapLoaded = 0;
struct LayerFile* LoadedFile;

unsigned char *ReadBinaryFile(const char *Filename, long *FileSize) {
    FILE *File = fopen(Filename, "rb"); // Open file in binary read mode
    if (!File) {
        perror("Error opening file");
        return NULL;
    }

    // Seek to end to determine file size
    fseek(File, 0, SEEK_END);
    *FileSize = ftell(File);
    rewind(File); // Reset file position

    // Allocate memory for the file content
    unsigned char *Buffer = (unsigned char *)malloc(*FileSize);
    if (!Buffer) {
        perror("Memory allocation failed");
        fclose(File);
        return NULL;
    }

    // Read file contents into buffer
    size_t BytesRead = fread(Buffer, 1, *FileSize, File);
    if (BytesRead != *FileSize) {
        perror("Error reading file");
        free(Buffer);
        fclose(File);
        return NULL;
    }

    fclose(File);
    return Buffer; // Return the buffer
}

void LoadBin(const char* FilePath)
{
    if(MapLoaded != 0)
    {
        //unload map here
    }
    unsigned long FileSize;
    unsigned char* File = ReadBinaryFile(FilePath, &FileSize);
    unsigned char* OrigFilePtr = File;

    LoadedFile = malloc(sizeof(struct LayerFile));
    LoadedFile->Header = READ_BE_TYPE(&File, uint32_t);
    LoadedFile->DeathOffset = *File;
    File++;

    uint8_t SectionCount = *OrigFilePtr;
    
    LoadedFile->Sections = malloc(sizeof(struct Section) * SectionCount);

    for(int ParsedSections = 0; ParsedSections < SectionCount; ParsedSections++)
    {
        struct Section* CurrentSection = &LoadedFile->Sections[ParsedSections];

        CurrentSection->AmmPartsInSubsections = *File;
        File++;
        CurrentSection->AmmSubsections = *File;
        File++;
        CurrentSection->HeightOffset = *File;
        File++;
        CurrentSection->SubsectionLength = 0x80;

        CurrentSection->SubSections = malloc(sizeof(struct SubSection) * 0xC00 / 0x80);

        for(int S = 0; S < (0xC00 / CurrentSection->SubsectionLength); S++)
        {
            struct SubSection* CurSubSection = &CurrentSection->SubSections[S];
            CurSubSection->HeaderbyteOne = *File;
            File++;
            CurSubSection->HeaderbyteTwo = *File;
            File++;

            CurSubSection->Data = malloc(sizeof(struct Tile) * CurrentSection->SubsectionLength / 2);

            for(int i = 0; i < CurrentSection->SubsectionLength; i += 2)
            {
                CurSubSection->Data[i].Byte1 = *File;
                File++;
                CurSubSection->Data[i].Byte2 = *File;
                File++;
            }
        }
    }

    free(File);
}
