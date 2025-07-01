//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// hyperloglog.cpp
//
// Identification: src/primer/hyperloglog.cpp
//
// Copyright (c) 2015-2025, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "primer/hyperloglog.h"

namespace bustub {

/** @brief Parameterized constructor. */
template <typename KeyType>
HyperLogLog<KeyType>::HyperLogLog(int16_t n_bits) : cardinality_(0) {}

/**
 * @brief Function that computes binary.
 *
 * @param[in] hash
 * @returns binary of a given hash
 */
template <typename KeyType>
auto HyperLogLog<KeyType>::ComputeBinary(const hash_t &hash) const -> std::bitset<BITSET_CAPACITY> {
  /** @TODO(student) Implement this function! */
  return {0};
}

/**
 * @brief Function that computes leading zeros.
 *
 * @param[in] bset - binary values of a given bitset
 * @returns leading zeros of given binary set
 */
template <typename KeyType>
auto HyperLogLog<KeyType>::PositionOfLeftmostOne(const std::bitset<BITSET_CAPACITY> &bset) const -> uint64_t {
  /** @TODO(student) Implement this function! */
  return 0;
}

/**
 * @brief Adds a value into the HyperLogLog.
 *
 * @param[in] val - value that's added into hyperloglog
 */
template <typename KeyType>
auto HyperLogLog<KeyType>::AddElem(KeyType val) -> void {
  /** @TODO(student) Implement this function! */
}

/**
 * @brief Function that computes cardinality.
 */
template <typename KeyType>
auto HyperLogLog<KeyType>::ComputeCardinality() -> void {
  /** @TODO(student) Implement this function! */
}

template class HyperLogLog<int64_t>;
template class HyperLogLog<std::string>;

}  // namespace bustub

uint64_t HyperLogLog::CalculateHash(std::string &a) {
    uint8_t hash_output[16];  // 128 bits = 16 bytes
    uint32_t seed = 0x12345678;  // 你可以选择任意固定种子

    // 进行哈希计算
    MurmurHash3_x86_128(a.data(), static_cast<int>(a.size()), seed, hash_output);

    // 提取前 8 字节（即前 64 位）作为最终返回值
    uint64_t result;
    std::memcpy(&result, hash_output, sizeof(uint64_t));
    return result;
}
HyperLogLog::HyperLogLog(int b) : b(b), m(1 << b), registers(m, 0) {
    // registers 被初始化为 m 个 0
}

void HyperLogLog::AddElem(uint64_t val) {
    uint64_t hash = CalculateHash(val);       // 假设是个64位的哈希值
    uint64_t index = hash >> (64 - b);        // 用前 b 位作为桶编号
    uint64_t suffix = hash << b;              // 后缀部分用于计算 rho

    int rho = PositionOfLeftmostOne(suffix) + 1;

    // 更新对应寄存器
    registers[index] = std::max(registers[index], rho);
}

int HyperLogLog::PositionOfLeftmostOne(uint64_t val) {
    if (val == 0) return 64;
    int pos = 1;
    while ((val & (1ULL << 63)) == 0) {
        val <<= 1;
        pos++;
    }
    return pos;
}

uint64_t HyperLogLog::ComputeCardinality(){
    double Z = 0.0;
    for (int r : registers) {
        Z += 1.0 / (1ULL << r);  // 或 std::exp2(-r)
    }
    Z = 1.0 / Z;
    return (factor * (1ULL << (2 * b))) / Z;
}





