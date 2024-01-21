#pragma once

#include <inttypes.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef u_int16_t u16;
typedef u_int32_t u32;
typedef u_int64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef size_t usize;

#define VEC_R                                                                                                          \
    CLITERAL(Vector2) { 1, 0 }
#define VEC_U                                                                                                          \
    CLITERAL(Vector2) { 0, -1 }
#define VEC_L                                                                                                          \
    CLITERAL(Vector2) { -1, 0 }
#define VEC_D                                                                                                          \
    CLITERAL(Vector2) { 0, 1 }

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))
