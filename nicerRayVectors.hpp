//------------------------------
// Header portion
//------------------------------
#ifndef NICER_RAYLIB_VECTORS_HPP
#define NICER_RAYLIB_VECTORS_HPP
#include "raylib.h"
#include "raymath.h"
#endif
//------------------------------





//------------------------------
// Start of Implementation
//------------------------------
#ifdef NICER_RAYLIB_VECTORS_IMPLEMENTATION
//Convenience macro
#define SpreadV2(vec2) vec2.x, vec2.y
#define SpreadV2Parallel(vecA, op, vecB) vecA.x op vecB.x, vecA.y op vecB.y
#define SpreadV2ParallelWithScalar(vec2, op, scalar) vec2.x op scalar, vec2.y op scalar

Vector2 operator + (Vector2 first, Vector2 second) { return {SpreadV2Parallel(first, +, second)}; }
Vector2 operator - (Vector2 first, Vector2 second) { return {SpreadV2Parallel(first, -, second)}; }
Vector3 operator + (Vector2 first, float scalar) { return {SpreadV2ParallelWithScalar(first, +, scalar)}; }
Vector3 operator - (Vector2 first, float scalar) { return {SpreadV2ParallelWithScalar(first, -, scalar)}; }
Vector2 operator * (Vector2 first, float scalarFactor) { return {SpreadV2ParallelWithScalar(first, *, scalarFactor)}; }
Vector2 operator / (Vector2 first, float scalarFactor) { return {SpreadV2ParallelWithScalar(first, /, scalarFactor)}; }

float VecDot(Vector2 a, Vector2 b) {return Vector2DotProduct(a, b);}
// Vector2 VecCross(Vector2 a, Vector2 b) {return Vector2CrossProduct(a, b);} //NOTE: Cross product is not defined for 2d vectors
#undef SpreadV2Parallel
#undef SpreadV2ParallelWithScalar


//Convenience macro
#define SpreadV3(vec3) vec3.x, vec3.y, vec3.z
#define SpreadV3Parallel(vecA, op, vecB) vecA.x op vecB.x, vecA.y op vecB.y, vecA.z op vecB.z
#define SpreadV3ParallelWithScalar(vec3, op, scalar) vec3.x op scalar, vec3.y op scalar, vec3.z op scalar


Vector3 operator + (Vector3 first, Vector3 second) { return {SpreadV3Parallel(first, +, second)}; }
Vector3 operator - (Vector3 first, Vector3 second) { return {SpreadV3Parallel(first, -, second)}; }
Vector3 operator + (Vector3 first, float scalar) { return {SpreadV3ParallelWithScalar(first, +, scalar)}; }
Vector3 operator - (Vector3 first, float scalar) { return {SpreadV3ParallelWithScalar(first, -, scalar)}; }
Vector3 operator * (Vector3 first, float scalarFactor) { return {SpreadV3ParallelWithScalar(first, *, scalarFactor)}; }
Vector3 operator / (Vector3 first, float scalarFactor) { return {SpreadV3ParallelWithScalar(first, /, scalarFactor)}; }

float VecDot(Vector3 a, Vector3 b) {return Vector3DotProduct(a, b);}
Vector3 VecCross(Vector3 a, Vector3 b) {return Vector3CrossProduct(a, b);}

//Pseudo-constructor for Vector2
Vector2 Vec(float x, float y) { return {x,y};}
//Pseudo-constructor for Vector3
Vector3 Vec(float x, float y, float z) { return {x,y,z};}
//Pseudo-constructor for Vector4
Vector4 Vec(float x, float y, float z, float w) { return {x,y,z,w};}

#undef SpreadV3Parallel
#undef SpreadV3ParallelWithScalar

//TODO: Vector4's
#endif