#ifndef MACROS_H_
#define MACROS_H_
#include <stdint.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif


#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

// Macro to check if the system is little-endian
#define IS_LITTLE_ENDIAN() (*(uint16_t *)"\x01\x00" == 0x0001)

// Generic macro to swap byte order
#define SWAP_ENDIAN(x) (_Generic((x), \
    uint16_t: (uint16_t)((((x) >> 8) & 0x00FF) | (((x) & 0x00FF) << 8)), \
    int16_t: (int16_t)((((uint16_t)(x) >> 8) & 0x00FF) | (((uint16_t)(x) & 0x00FF) << 8)), \
    uint32_t: (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24)), \
    int32_t: (int32_t)((((uint32_t)(x) >> 24) | (((uint32_t)(x) & 0x00FF0000) >> 8) | (((uint32_t)(x) & 0x0000FF00) << 8) | ((uint32_t)(x) << 24))), \
    uint64_t: (((x) >> 56) | \
              (((x) & 0x00FF000000000000) >> 40) | \
              (((x) & 0x0000FF0000000000) >> 24) | \
              (((x) & 0x000000FF00000000) >> 8)  | \
              (((x) & 0x00000000FF000000) << 8)  | \
              (((x) & 0x0000000000FF0000) << 24) | \
              (((x) & 0x000000000000FF00) << 40) | \
              ((x) << 56)), \
    int64_t: (int64_t)((((uint64_t)(x) >> 56) | \
              (((uint64_t)(x) & 0x00FF000000000000) >> 40) | \
              (((uint64_t)(x) & 0x0000FF0000000000) >> 24) | \
              (((uint64_t)(x) & 0x000000FF00000000) >> 8)  | \
              (((uint64_t)(x) & 0x00000000FF000000) << 8)  | \
              (((uint64_t)(x) & 0x0000000000FF0000) << 24) | \
              (((uint64_t)(x) & 0x000000000000FF00) << 40) | \
              ((uint64_t)(x) << 56)))))

// Macro to convert from big-endian to little-endian if the system is little-endian
#define BE_TO_LE(x) (IS_LITTLE_ENDIAN() ? SWAP_ENDIAN(x) : (x))

#define READ_BE_TYPE(FilePtr, Type) ({ \
    Type val = *(Type *)(*(FilePtr));  \
    *(FilePtr) += sizeof(Type);        \
    BE_TO_LE(val);                     \
})

#endif