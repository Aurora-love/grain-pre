#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Quaternion utilities
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GE {

// ==================== 类型定义 ====================

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;
using Quat = glm::quat;

// ==================== 数学常量 ====================
constexpr float PI = 3.14159265358979323846f;      // 圆周率
constexpr float TWO_PI = 2.0f * PI;                // 2π
constexpr float HALF_PI = PI * 0.5f;               // π/2
constexpr float QUARTER_PI = PI * 0.25f;           // π/4
constexpr float E = 2.71828182845904523536f;       // 自然常数 e
constexpr float DEG_TO_RAD = PI / 180.0f;          // 角度转弧度
constexpr float RAD_TO_DEG = 180.0f / PI;          // 弧度转角度

// ==================== 角度转换 ====================
/**
 * @brief 将角度 (degrees) 转换为弧度 (radians)
 *
 * @param degrees 角度值，单位为度 (°)。可以为任意实数（支持负值）。
 * @return 对应的弧度值，单位为弧度。
 */
float ToRadians(float degrees);

/**
 * @brief 将弧度 (radians) 转换为角度 (degrees)
 *
 * @param radians 弧度值，单位为弧度。
 * @return 对应的角度值，单位为度 (°)。
 */
float ToDegrees(float radians);

// ==================== 通用数学函数 ====================
/**
 * @brief 线性插值
 *
 * 计算 a 与 b 之间按比例 t 的线性插值：a + (b - a) * t。
 *
 * @tparam T 支持 +, -, * 运算符的数值或向量类型。
 * @param a 起始值（t=0 时返回 a）。
 * @param b 结束值（t=1 时返回 b）。
 * @param t 插值系数，通常在 [0,1] 范围内；可超出以做外插。
 * @return 插值结果，类型为 T。
 */
template<typename T>
inline T Lerp(const T& a, const T& b, float t) {
    return a + (b - a) * t;
}

/**
 * @brief 将值限制在指定范围内
 *
 * @tparam T 支持比较运算符的类型。
 * @param value 待限制的值。
 * @param min 最小值（包含）。
 * @param max 最大值（包含）。
 * @return 如果 value < min 返回 min；如果 value > max 返回 max；否则返回 value 本身。
 */
template<typename T>
inline T Clamp(const T& value, const T& min, const T& max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * @brief 返回两个值中的最小值
 * @tparam T 数值类型
 * @param a 第一个值
 * @param b 第二个值
 * @return 最小值
 */
template<typename T>
inline T Min(const T& a, const T& b) {
    return a < b ? a : b;
}

/**
 * @brief 返回两个值中的最大值
 * @tparam T 数值类型
 * @param a 第一个值
 * @param b 第二个值
 * @return 最大值
 */
template<typename T>
inline T Max(const T& a, const T& b) {
    return a > b ? a : b;
}

// ==================== 基础数学运算 ====================
/** @brief 计算非负输入的平方根
 *  @param value 被开方数（当为负时行为依赖实现，通常返回 NaN）
 *  @return sqrt(value)
 */
float Sqrt(float value);

/** @brief 绝对值
 *  @param value 实数输入
 *  @return |value|
 */
float Abs(float value);

/** @brief 正弦函数（输入为弧度）
 *  @param angle 弧度
 *  @return sin(angle)
 */
float Sin(float angle);

/** @brief 余弦函数（输入为弧度）
 *  @param angle 弧度
 *  @return cos(angle)
 */
float Cos(float angle);

/** @brief 正切函数（输入为弧度）
 *  @param angle 弧度
 *  @return tan(angle)
 */
float Tan(float angle);

/** @brief 反正弦（输出为弧度）
 *  @param value 输入值，建议范围 [-1,1]
 *  @return asin(value)（弧度）
 */
float Asin(float value);

/** @brief 反余弦（输出为弧度）
 *  @param value 输入值，建议范围 [-1,1]
 *  @return acos(value)（弧度）
 */
float Acos(float value);

/** @brief 反正切（输出为弧度）
 *  @param value 输入实数
 *  @return atan(value)（弧度）
 */
float Atan(float value);

/** @brief 反正切，考虑象限（输出弧度）
 *  @param y y 分量
 *  @param x x 分量
 *  @return atan2(y, x)（弧度），在 [-π, π] 范围内
 */
float Atan2(float y, float x);

/** @brief 幂运算
 *  @param base 底数
 *  @param exponent 指数
 *  @return pow(base, exponent)
 */
float Pow(float base, float exponent);

/** @brief 自然指数 e^value
 *  @param value 指数
 *  @return e^value
 */
float Exp(float value);

/** @brief 自然对数（以 e 为底）
 *  @param value 正数输入
 *  @return ln(value)
 */
float Log(float value);

/** @brief 以 10 为底的对数
 *  @param value 正数输入
 *  @return log10(value)
 */
float Log10(float value);

/** @brief 向下取整
 *  @param value 实数输入
 *  @return floor(value)
 */
float Floor(float value);

/** @brief 向上取整
 *  @param value 实数输入
 *  @return ceil(value)
 */
float Ceil(float value);

/** @brief 四舍五入到最接近的整数（以 float 返回）
 *  @param value 实数输入
 *  @return round(value)
 */
float Round(float value);

/** @brief 返回 value 的小数部分（value - floor(value)）
 *  @param value 实数输入
 *  @return 小数部分（非负）
 */
float Fract(float value);

// ==================== 距离计算 ====================
/**
 * @brief 计算两点之间的欧几里得距离 (2D)
 *
 * @param a 第一个点 (x,y)
 * @param b 第二个点 (x,y)
 * @return sqrt((a.x-b.x)^2 + (a.y-b.y)^2)
 */
float Distance(const Vec2& a, const Vec2& b);

/**
 * @brief 计算两点之间的欧几里得距离 (3D)
 *
 * @param a 第一个点 (x,y,z)
 * @param b 第二个点 (x,y,z)
 * @return sqrt((a.x-b.x)^2 + (a.y-b.y)^2 + (a.z-b.z)^2)
 */
float Distance(const Vec3& a, const Vec3& b);

/**
 * @brief 计算两点之间距离的平方 (2D)
 *
 * @note 返回平方距离以避免开方开销，适用于比较场景。
 * @param a 第一个点
 * @param b 第二个点
 * @return (a.x-b.x)^2 + (a.y-b.y)^2
 */
float DistanceSquared(const Vec2& a, const Vec2& b);

/**
 * @brief 计算两点之间距离的平方 (3D)
 *
 * @param a 第一个点
 * @param b 第二个点
 * @return (a.x-b.x)^2 + (a.y-b.y)^2 + (a.z-b.z)^2
 */
float DistanceSquared(const Vec3& a, const Vec3& b);

// ==================== 向量角度 ====================
/**
 * @brief 计算两个 2D 向量之间的夹角（弧度）
 *
 * @param from 起始向量；函数会对向量进行归一化以计算夹角。
 * @param to 目标向量；同上。
 * @return 夹角，单位为弧度，范围为 [0, π]
 */
float Angle(const Vec2& from, const Vec2& to);

/**
 * @brief 计算两个 3D 向量之间的夹角（弧度）
 *
 * @param from 起始向量，归一化后参与计算。
 * @param to 目标向量，归一化后参与计算。
 * @return 夹角，单位为弧度，范围为 [0, π]
 */
float Angle(const Vec3& from, const Vec3& to);

// ==================== 点积与叉积 ====================
/**
 * @brief 2D 向量点积（标量）
 *
 * @param a 第一个向量
 * @param b 第二个向量
 * @return a.x*b.x + a.y*b.y
 */
float Dot(const Vec2& a, const Vec2& b);

/**
 * @brief 3D 向量点积（标量）
 *
 * @param a 第一个向量
 * @param b 第二个向量
 * @return a.x*b.x + a.y*b.y + a.z*b.z
 */
float Dot(const Vec3& a, const Vec3& b);

/**
 * @brief 4D 向量点积（标量）
 *
 * @param a 第一个向量
 * @param b 第二个向量
 * @return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w
 */
float Dot(const Vec4& a, const Vec4& b);

/**
 * @brief 3D 向量叉积（向量）
 *
 * @param a 第一个向量
 * @param b 第二个向量
 * @return 向量垂直于 a 和 b，并遵循右手定则
 */
Vec3 Cross(const Vec3& a, const Vec3& b);

// ==================== 矩阵变换 ====================
/**
 * @brief 在已有矩阵上应用平移变换
 *
 * @param mat 输入矩阵（通常为模型矩阵或视图矩阵）
 * @param vec 平移量 (x,y,z)
 * @return 新的 4x4 矩阵，等价于 mat * T(vec)（取决于矩阵乘法约定）
 */
Mat4 Translate(const Mat4& mat, const Vec3& vec);

/**
 * @brief 在已有矩阵上应用绕轴旋转
 *
 * @param mat 输入矩阵
 * @param angle 旋转角度（弧度）
 * @param axis 旋转轴（不必归一化，内部会使用 glm 的实现）
 * @return 新的 4x4 矩阵，等价于 mat * R(angle, axis)
 */
Mat4 Rotate(const Mat4& mat, float angle, const Vec3& axis);

/**
 * @brief 在已有矩阵上应用缩放变换
 *
 * @param mat 输入矩阵
 * @param vec 缩放因子 (sx, sy, sz)
 * @return 新的 4x4 矩阵
 */
Mat4 Scale(const Mat4& mat, const Vec3& vec);

// ==================== 辅助函数 ====================
/**
 * @brief 获取数据的原始指针 (const)
 * @note 封装 glm::value_ptr
 */
template<typename T>
const float* ValuePtr(const T& value) { return glm::value_ptr(value); }

/**
 * @brief 获取数据的原始指针
 * @note 封装 glm::value_ptr
 */
template<typename T>
float* ValuePtr(T& value) { return glm::value_ptr(value); }

// ==================== 向量归一化 ====================
/**
 * @brief 将 2D 向量转换为单位向量（长度为 1）
 *
 * @param v 输入向量 (x,y)。若长度为 0 则返回 (0,0) 以避免 NaN。
 * @return 归一化后的向量，长度约为 1（若输入长度为 0 则返回零向量）。
 */
Vec2 Normalize(const Vec2& v);

/**
 * @brief 将 3D 向量转换为单位向量（长度为 1）
 *
 * @param v 输入向量 (x,y,z)。若长度为 0 则返回 (0,0,0) 以避免 NaN。
 * @return 归一化后的向量，长度约为 1（若输入长度为 0 则返回零向量）。
 */
Vec3 Normalize(const Vec3& v);

/**
 * @brief 将 4D 向量转换为单位向量（长度为 1）
 *
 * @note 对于使用齐次坐标 (x,y,z,w) 的场景，通常不应直接对整个 Vec4 做归一化；
 *       本函数按分量计算长度并归一化整向量，仅在确实需要按四维长度归一化时使用。
 * @param v 输入向量 (x,y,z,w)。若长度为 0 则返回 (0,0,0,0)。
 * @return 归一化后的 Vec4。
 */
Vec4 Normalize(const Vec4& v);

// ==================== 向量长度 ====================
/** @brief 计算向量的欧几里得长度 */
float Length(const Vec2& v);
/** @brief 计算向量的欧几里得长度 */
float Length(const Vec3& v);
/** @brief 计算向量的欧几里得长度 */
float Length(const Vec4& v);

/** @brief 计算向量长度的平方（避免开方运算） */
float LengthSquared(const Vec2& v);
/** @brief 计算向量长度的平方（避免开方运算） */
float LengthSquared(const Vec3& v);
/** @brief 计算向量长度的平方（避免开方运算） */
float LengthSquared(const Vec4& v);

// ==================== 向量反射与折射 ====================
/** @brief 计算向量关于法线的反射向量 */
Vec2 Reflect(const Vec2& v, const Vec2& normal);
/** @brief 计算向量关于法线的反射向量 */
Vec3 Reflect(const Vec3& v, const Vec3& normal);

/** @brief 计算向量关于法线的折射向量 */
Vec2 Refract(const Vec2& v, const Vec2& normal, float eta);
/** @brief 计算向量关于法线的折射向量 */
Vec3 Refract(const Vec3& v, const Vec3& normal, float eta);

// ==================== 矩阵转置 ====================
/**
 * @brief 将 2x2 矩阵的行和列互换
 *
 * @param m 输入 2x2 矩阵
 * @return 转置后的 2x2 矩阵
 */
Mat2 Transpose(const Mat2& m);

/**
 * @brief 将 3x3 矩阵的行和列互换
 *
 * @param m 输入 3x3 矩阵
 * @return 转置后的 3x3 矩阵
 */
Mat3 Transpose(const Mat3& m);

/**
 * @brief 将 4x4 矩阵的行和列互换
 *
 * @param m 输入 4x4 矩阵
 * @return 转置后的 4x4 矩阵
 */
Mat4 Transpose(const Mat4& m);

// ==================== 矩阵求逆 ====================
/**
 * @brief 计算 2x2 矩阵的逆矩阵
 *
 * @param m 输入 2x2 矩阵
 * @return 逆矩阵，若矩阵不可逆（行列式为 0）行为依赖实现（可能为未定义）
 */
Mat2 Inverse(const Mat2& m);

/**
 * @brief 计算 3x3 矩阵的逆矩阵
 *
 * @param m 输入 3x3 矩阵
 * @return 逆矩阵
 */
Mat3 Inverse(const Mat3& m);

/**
 * @brief 计算 4x4 矩阵的逆矩阵
 *
 * @param m 输入 4x4 矩阵
 * @return 逆矩阵
 */
Mat4 Inverse(const Mat4& m);

// ==================== 矩阵行列式 ====================
/**
 * @brief 计算 2x2 矩阵的行列式
 * @param m 输入 2x2 矩阵
 * @return 行列式值
 */
float Determinant(const Mat2& m);

/**
 * @brief 计算 3x3 矩阵的行列式
 * @param m 输入 3x3 矩阵
 * @return 行列式值
 */
float Determinant(const Mat3& m);

/**
 * @brief 计算 4x4 矩阵的行列式
 * @param m 输入 4x4 矩阵
 * @return 行列式值
 */
float Determinant(const Mat4& m);

// ==================== 单位矩阵 ====================
/**
 * @brief 返回 2x2 单位矩阵
 * @return 对角为 1 的 2x2 单位矩阵
 */
Mat2 Identity2();

/**
 * @brief 返回 3x3 单位矩阵
 * @return 对角为 1 的 3x3 单位矩阵
 */
Mat3 Identity3();

/**
 * @brief 返回 4x4 单位矩阵
 * @return 对角为 1 的 4x4 单位矩阵
 */
Mat4 Identity4();

// ==================== 变换矩阵 ====================
/**
 * @brief 创建平移变换矩阵
 *
 * @param translation 平移向量 (tx, ty, tz)
 * @return 4x4 平移矩阵，用于将点或变换平移 translation
 */
Mat4 Translation(const Vec3& translation);

/**
 * @brief 创建平移变换矩阵（分量形式）
 *
 * @param x 平移 x 分量
 * @param y 平移 y 分量
 * @param z 平移 z 分量
 * @return 4x4 平移矩阵
 */
Mat4 Translation(float x, float y, float z);

/**
 * @brief 创建绕指定轴旋转的 4x4 变换矩阵
 *
 * @param angle 旋转角度（弧度）
 * @param axis 旋转轴（不必归一化，内部会处理）
 * @return 4x4 旋转矩阵
 */
Mat4 Rotation(float angle, const Vec3& axis);

/** @brief 创建绕 X 轴旋转的 4x4 变换矩阵 (弧度) */
Mat4 RotationX(float angle);
/** @brief 创建绕 Y 轴旋转的 4x4 变换矩阵 (弧度) */
Mat4 RotationY(float angle);
/** @brief 创建绕 Z 轴旋转的 4x4 变换矩阵 (弧度) */
Mat4 RotationZ(float angle);

/**
 * @brief 创建缩放变换矩阵
 *
 * @param scale 缩放因子 (sx, sy, sz)
 * @return 4x4 缩放矩阵
 */
Mat4 Scale(const Vec3& scale);

/**
 * @brief 创建缩放变换矩阵（分量形式）
 *
 * @param x sx
 * @param y sy
 * @param z sz
 * @return 4x4 缩放矩阵
 */
Mat4 Scale(float x, float y, float z);

// ==================== 视图与投影矩阵 ====================
/**
 * @brief 创建视图矩阵（摄像机朝向）
 *
 * @param eye 摄像机位置
 * @param center 相机朝向的目标点位置
 * @param up 指定世界的上方向向量（不必归一化）
 * @return 视图矩阵，可用于将世界空间点变换到视图空间
 */
Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

/**
 * @brief 创建正交投影矩阵
 *
 * @param left 视区左边界
 * @param right 视区右边界
 * @param bottom 视区下边界
 * @param top 视区上边界
 * @param near 近裁剪面
 * @param far 远裁剪面
 * @return 正交投影矩阵
 */
Mat4 Ortho(float left, float right, float bottom, float top, float near, float far);

/**
 * @brief 创建简化的正交投影矩阵（忽略 near/far）
 *
 * @param left 视区左边界
 * @param right 视区右边界
 * @param bottom 视区下边界
 * @param top 视区上边界
 * @return 正交投影矩阵
 */
Mat4 Ortho(float left, float right, float bottom, float top);

/**
 * @brief 创建透视投影矩阵
 *
 * @param fov 垂直视场角（弧度）
 * @param aspect 宽高比（width/height）
 * @param near 近裁剪面
 * @param far 远裁剪面
 * @return 透视投影矩阵
 */
Mat4 Perspective(float fov, float aspect, float near, float far);

/**
 * @brief 基于宽高创建透视投影矩阵
 *
 * @param fov 视场角（弧度）
 * @param width 视口宽度
 * @param height 视口高度
 * @param near 近裁剪面
 * @param far 远裁剪面
 * @return 透视投影矩阵
 */
Mat4 Perspective(float fov, float width, float height, float near, float far);

/**
 * @brief 创建视锥体裁剪矩阵
 *
 * @param left 视锥左边界
 * @param right 视锥右边界
 * @param bottom 视锥下边界
 * @param top 视锥上边界
 * @param near 近裁剪面
 * @param far 远裁剪面
 * @return 透视投影矩阵（手动指定 frustum）
 */
Mat4 Frustum(float left, float right, float bottom, float top, float near, float far);

// ==================== 四元数操作 ====================
/** @brief 返回单位四元数（无旋转） */
Quat QuaternionIdentity();

/** @brief 从轴角创建四元数
 *  @param axis 旋转轴（函数实现会归一化；若为零向量将使用 (0,0,1) 作为默认轴）
 *  @param angle 旋转角度，单位为弧度
 *  @return 对应的四元数
 */
Quat QuaternionFromAxisAngle(const Vec3& axis, float angle);

/** @brief 从欧拉角创建四元数
 *  @param euler 三分量欧拉角 (pitch, yaw, roll)，每个分量单位为弧度
 *  @note 组件语义：euler.x = pitch (绕 X)，euler.y = yaw (绕 Y)，euler.z = roll (绕 Z)。
 *        使用 GLM 的 `quat` 约定构造四元数（组件分别表示绕 X/Y/Z 的旋转）。
 */
Quat QuaternionFromEuler(const Vec3& euler);

/** @brief 从欧拉角创建四元数（显式参数）
 *  @param pitch 绕 X 轴的角度（弧度）
 *  @param yaw   绕 Y 轴的角度（弧度）
 *  @param roll  绕 Z 轴的角度（弧度）
 */
Quat QuaternionFromEuler(float pitch, float yaw, float roll);

/** @brief 将四元数转换为欧拉角（弧度）
 *  @return 返回 (pitch, yaw, roll)，单位为弧度，按与 `QuaternionFromEuler` 对应的分量语义。
 */
Vec3 QuaternionToEuler(const Quat& q);

/** @brief 四元数乘法（组合旋转）
 *  @note 返回 `a * b`，按照四元数组合语义即先应用 `b` 的旋转再应用 `a` 的旋转（与 GLM 的乘法顺序一致）。
 */
Quat QuaternionMultiply(const Quat& a, const Quat& b);

/** @brief 四元数球面线性插值 (Slerp) */
Quat QuaternionSlerp(const Quat& a, const Quat& b, float t);

/** @brief 归一化四元数（确保数值稳定） */
Quat QuaternionNormalize(const Quat& q);

/** @brief 四元数共轭 */
Quat QuaternionConjugate(const Quat& q);

/** @brief 四元数逆 */
Quat QuaternionInverse(const Quat& q);

/** @brief 将四元数转换为 4x4 旋转矩阵 */
Mat4 QuaternionToMat4(const Quat& q);

// ==================== 比较函数 ====================
/**
 * @brief 判断两个浮点数是否近似相等
 *
 * @param a 第一个值
 * @param b 第二个值
 * @param epsilon 基础容差（相对误差因子），默认 1e-4
 * @return 若 |a-b| <= epsilon * max(1, |a|, |b|) 返回 true
 *
 * @note 使用相对误差可以避免在大量级坐标下绝对容差过小导致比较总为 false 的问题。
 */
bool Approximately(float a, float b, float epsilon = 0.0001f);

/**
 * @brief 判断两个 2D 向量是否近似相等（按量级缩放容差）
 *
 * @param a 第一个向量
 * @param b 第二个向量
 * @param epsilon 基础容差（相对误差因子）
 * @return 若距离平方 <= (epsilon * max(1, |a|, |b|))^2 返回 true
 */
bool Approximately(const Vec2& a, const Vec2& b, float epsilon = 0.0001f);

/**
 * @brief 判断两个 3D 向量是否近似相等（按量级缩放容差）
 *
 * @param a 第一个向量
 * @param b 第二个向量
 * @param epsilon 基础容差（相对误差因子）
 * @return 若距离平方 <= (epsilon * max(1, |a|, |b|))^2 返回 true
 */
bool Approximately(const Vec3& a, const Vec3& b, float epsilon = 0.0001f);

/**
 * @brief 判断是否为 NaN（非数字）
 * @param value 浮点数
 * @return 若 value 为 NaN 返回 true
 */
bool IsNaN(float value);

/**
 * @brief 判断是否为无穷大（正/负无穷）
 * @param value 浮点数
 * @return 若 value 为 +Inf 或 -Inf 返回 true
 */
bool IsInf(float value);

// ==================== 位运算相关 ====================
/**
 * @brief 判断是否为 2 的幂次方
 * @param value 整数（应为正）
 * @return 若 value 为 2 的幂返回 true
 */
bool IsPowerOfTwo(int value);

/**
 * @brief 返回大于等于 value 的最小 2 的幂次方
 *
 * @param value 输入整数（若 <=0 返回 0）
 * @return 最小的 2 的幂次方，大于等于 value
 */
int NextPowerOfTwo(int value);

// ==================== 插值函数 ====================
/**
 * @brief 平滑插值：在 edge0 和 edge1 之间进行平滑过渡
 *
 * 当 x <= edge0 返回 0，当 x >= edge1 返回 1，中间按 Hermite 多项式平滑过渡。
 * @param edge0 下边界
 * @param edge1 上边界
 * @param x 输入值
 * @return 平滑插值值（0..1）
 */
float Smoothstep(float edge0, float edge1, float x);

/**
 * @brief 阶跃函数
 *
 * @param edge 阈值
 * @param x 输入值
 * @return 若 x < edge 返回 0，否则返回 1
 */
float Step(float edge, float x);

// ==================== 旋转变换 ====================
/**
 * @brief 将 2D 向量旋转指定角度（弧度）
 *
 * @param v 输入向量 (x,y)
 * @param angle 旋转角度，单位为弧度，逆时针为正（右手系）
 * @return 旋转后的向量
 */
Vec2 Rotate(const Vec2& v, float angle);

/**
 * @brief 将点绕指定中心和轴旋转
 *
 * @param point 被旋转的点
 * @param center 旋转中心点
 * @param axis 旋转轴（函数实现会归一化轴；若为零向量使用默认轴）
 * @param angle 旋转角度，单位为弧度
 * @return 旋转后的位置
 */
Vec3 RotateAround(const Vec3& point, const Vec3& center, const Vec3& axis, float angle);

// ==================== 组合变换 ====================
/**
 * @brief 创建 TRS（平移-旋转-缩放）变换矩阵
 *
 * 变换顺序为 T * R * S（先缩放，再旋转，最后平移），返回用于把局部坐标变换到世界坐标的矩阵。
 *
 * @param translation 平移向量 (tx, ty, tz)
 * @param rotation 旋转四元数（函数不对其进行归一化检查，建议传入归一化四元数）
 * @param scale 缩放向量 (sx, sy, sz)
 * @return 组合后的 4x4 变换矩阵
 */
Mat4 TRS(const Vec3& translation, const Quat& rotation, const Vec3& scale);

}
