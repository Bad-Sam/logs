// Number to string conversion functions.
//
// Example usage:
//
//   u8     buffer[F32_STR_MAX_SIZE];
//   float  num = -12345.06789f
//   u32    str_size = f32_to_str(buffer, num);
#pragma once

#include "types.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//// Helper
typedef enum num_str_max_size
{
  U8_STR_MAX_SIZE  = 3,
  U16_STR_MAX_SIZE = 5,
  U32_STR_MAX_SIZE = 10,
  U64_STR_MAX_SIZE = 20,
  S8_STR_MAX_SIZE  = 4,
  S16_STR_MAX_SIZE = 6,
  S32_STR_MAX_SIZE = 11,
  S64_STR_MAX_SIZE = 20,
  F32_STR_MAX_SIZE = 18,
  HEX_STR_MAX_SIZE = 18,
  BIN_STR_MAX_SIZE = 66
} num_str_max_size;


///////////////////////////////////////////////////////////////////////////////////////////////////
//// Utility
u32 u32_str_size(u32 num);
u32 u64_str_size(u64 num);


///////////////////////////////////////////////////////////////////////////////////////////////////
//// Formatting
// Inputs:
// - buffer:   a pointer to the first character of a buffer, where the number's string will start.
//             The value of enum num_str_max_size indicates the maximum amount of characters needed
//             in the buffer for each supported type. However, the capacity of the buffer can be
//             lower, depending on the range of the passed number. It is up to the caller to pass a
//             sufficiently big buffer
// - num/data: the number/data to write in the buffer. Each function may write several digits, a
//             period, a negative sign and a base prefix (0b, 0x) to the buffer
//
// Output: amount of characters written to the buffer, such that buffer + output points to the
//         end of the string, i.e. the first character after the number's string
//
// By default, values are written in base 10, hex_to_str() and bin_to_str() being the exceptions

// Prefer over u64_to_str() for unsigned values that can be represented with 32 bits or less
u32 u32_to_str(schar8* buffer, u32 num);

// Slower than u32_to_str(), use only for unsigned values that need more than 32 bits
u32 u64_to_str(schar8* buffer, u64 num);

// Prefer over s64_to_str() for signed values that can be represented with 32 bits or less
u32 s32_to_str(schar8* buffer, s32 num);

// Slower than s32_to_str(), use only for unsigned values that need more than 32 bits
u32 s64_to_str(schar8* buffer, s64 num);

// Writes floating-point values up to -/+ 2,147,483,648 with 6 fractional digits.
// NaN and infinities are represented as -/+ 2,147,483,648, depending on the sign bit
u32 f32_to_str(schar8* buffer, f32 num);

// Writes nibble_count nibbles of a u32 as an hexadecimal string. nibble_count is
// expected to be 1 or greater
u32 u32_to_sized_hex_str(schar8* buffer, u32 num, u32 nibble_count);

// Writes nibble_count nibbles of a u64 as an hexadecimal string. nibble_count is
// expected to be 1 or greater
u32 u64_to_sized_hex_str(schar8* buffer, u64 num, u32 nibble_count);

// Writes bit_count bits of a u32 as an binary string. bit_count is expected to be
// 1 or greater
u32 u32_to_sized_bin_str(schar8* buffer, u32 num, u32 bit_count);

// Writes bit_count bits of a u64 as an binary string. bit_count is expected to be
// 1 or greater
u32 u64_to_sized_bin_str(schar8* buffer, u64 num, u32 bit_count);

// Writes only the significant nibbles of a u32 as an hexadecimal string
u32 u32_to_min_hex_str(schar8* buffer, u32 num);

// Writes only the significant nibbles of a u64 as an hexadecimal string
u32 u64_to_min_hex_str(schar8* buffer, u64 num);

// Writes only the significant bits of a u32 as an hexadecimal string
u32 u32_to_min_bin_str(schar8* buffer, u32 num);

// Writes only the significant bits of a u64 as an hexadecimal string
u32 u64_to_min_bin_str(schar8* buffer, u64 num);
