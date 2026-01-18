#include "CoreMath.h"
#include <cmath>
namespace GE {

float ToRadians(float degrees) { return degrees * DEG_TO_RAD; }
float ToDegrees(float radians) { return radians * RAD_TO_DEG; }
float Sqrt(float value) { return std::sqrt(value); }
float Abs(float value) { return std::abs(value); }
float Sin(float value) { return std::sin(value); }
float Cos(float angle) { return std::cos(angle); }
float Tan(float angle) { return std::tan(angle); }
float Asin(float value) { return std::asin(value); }
float Acos(float value) { return std::acos(value); }
float Atan(float value) { return std::atan(value); }
float Atan2(float y, float x) { return std::atan2(y, x); }
float Pow(float base, float exponent) { return std::pow(base, exponent); }
float Exp(float value) { return std::exp(value); }
float Log(float value) { return std::log(value); }
float Log10(float value) { return std::log10(value); }
float Floor(float value) { return std::floor(value); }
float Ceil(float value) { return std::ceil(value); }
float Round(float value) { return std::round(value); }
float Fract(float value) { return value - Floor(value); }
Mat4 Translate(const Mat4& mat, const Vec3& vec) { return glm::translate(mat, vec); }
Mat4 Rotate(const Mat4& mat, float angle, const Vec3& axis) { return glm::rotate(mat, angle, axis); }
Mat4 Scale(const Mat4& mat, const Vec3& vec) { return glm::scale(mat, vec); }
Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar) { return glm::ortho(left, right, bottom, top, zNear, zFar); }
Mat4 Ortho(float left, float right, float bottom, float top) { return glm::ortho(left, right, bottom, top); }
Mat4 Inverse(const Mat4& mat) { return glm::inverse(mat); }
float Distance(const Vec2& a, const Vec2& b) { return glm::distance(a, b); }
float Distance(const Vec3& a, const Vec3& b) { return glm::distance(a, b); }
float DistanceSquared(const Vec2& a, const Vec2& b) { return Dot(a - b, a - b); }
float DistanceSquared(const Vec3& a, const Vec3& b) { return Dot(a - b, a - b); }
float Angle(const Vec2& from, const Vec2& to) { return std::acos(Clamp(Dot(Normalize(from), Normalize(to)), -1.0f, 1.0f)); }
float Angle(const Vec3& from, const Vec3& to) { return std::acos(Clamp(Dot(Normalize(from), Normalize(to)), -1.0f, 1.0f)); }
float Dot(const Vec2& a, const Vec2& b) { return glm::dot(a, b); }
float Dot(const Vec3& a, const Vec3& b) { return glm::dot(a, b); }
float Dot(const Vec4& a, const Vec4& b) { return glm::dot(a, b); }
Vec3 Cross(const Vec3& a, const Vec3& b) { return glm::cross(a, b); }
Vec2 Normalize(const Vec2& v) { float l = glm::length(v); return l > 0.0f ? v / l : Vec2(0.0f); }
Vec3 Normalize(const Vec3& v) { float l = glm::length(v); return l > 0.0f ? v / l : Vec3(0.0f); }
Vec4 Normalize(const Vec4& v) { float l = glm::length(v); return l > 0.0f ? v / l : Vec4(0.0f); }
float Length(const Vec2& v) { return glm::length(v); }
float Length(const Vec3& v) { return glm::length(v); }
float Length(const Vec4& v) { return glm::length(v); }
float LengthSquared(const Vec2& v) { return Dot(v, v); }
float LengthSquared(const Vec3& v) { return Dot(v, v); }
float LengthSquared(const Vec4& v) { return Dot(v, v); }
Vec2 Reflect(const Vec2& v, const Vec2& normal) { return glm::reflect(v, normal); }
Vec3 Reflect(const Vec3& v, const Vec3& normal) { return glm::reflect(v, normal); }
Vec2 Refract(const Vec2& v, const Vec2& normal, float eta) { return glm::refract(v, normal, eta); }
Vec3 Refract(const Vec3& v, const Vec3& normal, float eta) { return glm::refract(v, normal, eta); }
Mat2 Transpose(const Mat2& m) { return glm::transpose(m); }
Mat3 Transpose(const Mat3& m) { return glm::transpose(m); }
Mat4 Transpose(const Mat4& m) { return glm::transpose(m); }
Mat2 Inverse(const Mat2& m) { return glm::inverse(m); }
Mat3 Inverse(const Mat3& m) { return glm::inverse(m); }
float Determinant(const Mat2& m) { return glm::determinant(m); }
float Determinant(const Mat3& m) { return glm::determinant(m); }
float Determinant(const Mat4& m) { return glm::determinant(m); }
Mat2 Identity2() { return Mat2(1.0f); }
Mat3 Identity3() { return Mat3(1.0f); }
Mat4 Identity4() { return Mat4(1.0f); }
Mat4 Translation(const Vec3& translation) { return glm::translate(Identity4(), translation); }
Mat4 Translation(float x, float y, float z) { return glm::translate(Identity4(), Vec3(x, y, z)); }
Mat4 Rotation(float angle, const Vec3& axis) { return glm::rotate(Identity4(), angle, axis); }
Mat4 RotationX(float angle) { return glm::rotate(Identity4(), angle, Vec3(1.0f, 0.0f, 0.0f)); }
Mat4 RotationY(float angle) { return glm::rotate(Identity4(), angle, Vec3(0.0f, 1.0f, 0.0f)); }
Mat4 RotationZ(float angle) { return glm::rotate(Identity4(), angle, Vec3(0.0f, 0.0f, 1.0f)); }
Mat4 Scale(const Vec3& scale) { return glm::scale(Identity4(), scale); }
Mat4 Scale(float x, float y, float z) { return glm::scale(Identity4(), Vec3(x, y, z)); }
Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) { return glm::lookAt(eye, center, up); }
Mat4 Perspective(float fov, float aspect, float zNear, float zFar) { return glm::perspective(fov, aspect, zNear, zFar); }
Mat4 Perspective(float fov, float width, float height, float zNear, float zFar) { return glm::perspectiveFov(fov, width, height, zNear, zFar); }
Mat4 Frustum(float left, float right, float bottom, float top, float zNear, float zFar) { return glm::frustum(left, right, bottom, top, zNear, zFar); }
Quat QuaternionIdentity() { return Quat(1.0f, 0.0f, 0.0f, 0.0f); } // w, x, y, z
Quat QuaternionFromAxisAngle(const Vec3& axis, float angle) {
    float len = glm::length(axis);
    Vec3 n = len > 0.0f ? axis / len : Vec3(0.0f, 0.0f, 1.0f);
    return glm::angleAxis(angle, n);
}
Quat QuaternionFromEuler(const Vec3& euler) { return glm::quat(euler); }
Quat QuaternionFromEuler(float pitch, float yaw, float roll) { return glm::quat(Vec3(pitch, yaw, roll)); }
Vec3 QuaternionToEuler(const Quat& q) { return glm::eulerAngles(q); }
Quat QuaternionMultiply(const Quat& a, const Quat& b) { return a * b; }
Quat QuaternionSlerp(const Quat& a, const Quat& b, float t) { return glm::slerp(a, b, t); }
Quat QuaternionNormalize(const Quat& q) { return glm::normalize(q); }
Quat QuaternionConjugate(const Quat& q) { return glm::conjugate(q); }
Quat QuaternionInverse(const Quat& q) { return glm::inverse(q); }
Mat4 QuaternionToMat4(const Quat& q) { return glm::mat4_cast(q); }
bool Approximately(float a, float b, float epsilon){
    float diff = Abs(a - b);
    float scale = Max(1.0f, Max(Abs(a), Abs(b)));
    return diff <= epsilon * scale;
}
bool Approximately(const Vec2& a, const Vec2& b, float epsilon){
    float dsq = DistanceSquared(a, b);
    float la = Length(a);
    float lb = Length(b);
    float scale = Max(1.0f, Max(la, lb));
    float tol = epsilon * scale;
    return dsq <= tol * tol;
}
bool Approximately(const Vec3& a, const Vec3& b, float epsilon){
    float dsq = DistanceSquared(a, b);
    float la = Length(a);
    float lb = Length(b);
    float scale = Max(1.0f, Max(la, lb));
    float tol = epsilon * scale;
    return dsq <= tol * tol;
}
bool IsNaN(float value) { return std::isnan(value); }
bool IsInf(float value) { return std::isinf(value); }
bool IsPowerOfTwo(int value) { return value > 0 && (value & (value - 1)) == 0; }
int NextPowerOfTwo(int value) {
	if (value <= 0) return 0;
    --value;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return value + 1;
}
float Smoothstep(float edge0, float edge1, float x) {
    float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}
float Step(float edge, float x) { return x < edge ? 0.0f : 1.0f; }
Vec2 Rotate(const Vec2& v, float angle) {
    float s = Sin(angle);
    float c = Cos(angle);
    return Vec2(v.x * c - v.y * s, v.x * s + v.y * c);
}
Vec3 RotateAround(const Vec3& point, const Vec3& center, const Vec3& axis, float angle) {
    Quat q = QuaternionFromAxisAngle(axis, angle);
    Vec3 diff = point - center;
    Mat4 rot = QuaternionToMat4(q);
    Vec3 rotated = Vec3(rot * Vec4(diff, 0.0f));
    return center + rotated;
}
Mat4 TRS(const Vec3& translation, const Quat& rotation, const Vec3& scale) {
    Mat4 t = Translation(translation);
    Mat4 r = QuaternionToMat4(rotation);
    Mat4 s = Scale(scale);
    return t * r * s;
}
}