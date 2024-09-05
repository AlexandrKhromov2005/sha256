#pragma once
#include <bitset>
#include <string>
#include <array>
#include <cstdint>
#include <sstream>
/// <summary>
/// bitsetToHexString
/// </summary>
/// <param name="bits"> битбокс</param>
/// <returns>stroka</returns>
std::string bitsetToHexString(const std::bitset<32>& bits) {
    uint32_t value = bits.to_ulong();
    std::stringstream ss;
    ss << std::hex << value;
    return ss.str();
}
/// <summary>
/// menyaet vse biti ns drugie
/// </summary>
/// <param name="a"></param>
/// <returns>bitset no naoborot</returns>
std::bitset<32> flipForBitset(std::bitset<32> a) {
    std::bitset<32> res = a;
    for (int i = 0; i < 32; i++) {
        res.flip(i);
    }
    return res;
}
/// <summary>
/// logical and
/// </summary>
/// <param name="a">bitset</param>
/// <param name="b">bitset</param>
/// <returns>da</returns>
std::bitset<32> andForBitset(const std::bitset<32>& a, const std::bitset<32>& b) {
    std::bitset<32> res;
    for (int i = 0; i < 32; i++) {
        res[i] = a[i] && b[i];
    }
    return res;
}
/// <summary>
/// slozhenie
/// </summary>
/// <param name="a">bitset</param>
/// <param name="b">bitset</param>
/// <returns>summa</returns>
std::bitset<32> addBitsets(const std::bitset<32>& a, const std::bitset<32>& b) {
    std::bitset<32> res;
    bool carry = 0;
    for (int i = 0; i < 32; i++) {
        int temp_sum = a[i] + b[i] + carry;
        switch (temp_sum)
        {
        case 1:
            res.set(i);
            carry = 0;
            break;
        case 2:
            carry = 1;
            break;
        case 3:
            res.set(i);
            carry = 1;
            break;
        }
    }
    return res;
}
/// <summary>
/// xor dlya treh bitsetov
/// </summary>
/// <param name="a">bitset</param>
/// <param name="b">bitset</param>
/// <param name="c">bitset</param>
/// <returns>bitset no tolko xor</returns>
std::bitset<32> xorBitsetsTriple(const std::bitset<32>& a, const std::bitset<32>& b, const std::bitset<32>& c) {
    std::bitset<32> result;
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i] ^ c[i];
    }
    return result;
}
/// <summary>
/// xor dlya dvuh
/// </summary>
/// <param name="a">bitset</param>
/// <param name="b">bitset</param>
/// <returns>bitset no tolko bitbox</returns>
std::bitset<32> xorBitsets(const std::bitset<32>& a, const std::bitset<32>& b) {
    std::bitset<32> result;
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] ^ b[i];
    }
    return result;
}
/// <summary>
/// vrashaite baraban
/// </summary>
/// <param name="bits">bitset</param>
/// <param name="n">sdvigi</param>
/// <returns>bitset</returns>
std::bitset<32> rightRotate(std::bitset<32> bits, int n) {
    std::bitset<32> res;
    for (int i = 0; i < 32; i++) {
        res[(i - n + 32) % 32] = bits[i];
    }
    return res;
}

/// <summary>
/// perevodit cho ugodno v bitset
/// </summary>
/// <typeparam name="T">ahahahaha</typeparam>
/// <param name="variable">peremenaya</param>
/// <returns>resultat</returns>
template <typename T>
std::bitset<sizeof(T)* CHAR_BIT> variableToBitset(const T& variable) {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&variable);
    std::bitset<sizeof(T)* CHAR_BIT> bits;

    for (size_t i = 0; i < sizeof(T); ++i) {
        for (size_t j = 0; j < CHAR_BIT; ++j) {
            bits[i * CHAR_BIT + j] = (bytes[i] >> j) & 1;
        }
    }

    return bits;
}
//concatanation of 3 bitsets
template <size_t N, size_t M, size_t O>
std::bitset<N + M + O> concat_bitsets(const std::bitset<N>& bs1, const std::bitset<M>& bs2, const std::bitset<O>& bs3) {
    std::string s1 = bs1.to_string();
    std::string s2 = bs2.to_string();
    std::string s3 = bs3.to_string();
    std::string result_str = s1 + s2 + s3;
    return std::bitset<N + M + O>(result_str);
}
/// <summary>
/// sha256 moei realizacii
/// </summary>
/// <typeparam name="T">ahahahahha</typeparam>
/// <param name="message">to chto nuzhno zahasit</param>
/// <returns>hashshhsshh</returns>
template <typename T>
std::string sha256(T message) {
    std::bitset<sizeof(T)* CHAR_BIT> bit_message = variableToBitset(message);
    int message_size = size(bit_message);
    std::bitset<sizeof(message_size)* CHAR_BIT> bit_message_size = variableToBitset(message_size);
    std::bitset<512 - ((size(bit_message) + size(bit_message_size)) % 512)> zeros_bitset;
    zeros_bitset[0] = 1;
    std::bitset<size(bit_message) + size(bit_message_size) + size(zeros_bitset)> bit_body = concat_bitsets(bit_message_size, zeros_bitset, bit_message);
    //consts
    uint32_t h[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
    uint32_t k[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };
    std::bitset<32> h_bits[8];
    for (int i = 0; i < 8; i++) {
        h_bits[i] = std::bitset<32>(h[i]);
    }

    std::bitset<32> w[64];

    for (int i = 0; i < bit_body.size(); i++) {
        w[i / 32][i % 32] = bit_body[i];
    }
    for (int i = 16; i < 64; i++) {
        std::bitset<32> s0 = xorBitsetsTriple(rightRotate(w[i - 15], 7), rightRotate(w[i - 15], 18), w[i - 15] >> 3);
        std::bitset<32> s1 = xorBitsetsTriple(rightRotate(w[i - 2], 17), rightRotate(w[i - 2], 19), w[i - 2] >> 10);
        w[i] = std::bitset<32>(w[i - 16].to_ulong() + s0.to_ulong() + w[i - 7].to_ulong() + s1.to_ulong());
    }

    for (int i = 0; i < 64; i++) {
        std::bitset<32> s1 = xorBitsetsTriple(rightRotate(h_bits[4], 6), rightRotate(h_bits[4], 11), rightRotate(h_bits[4], 25));

        std::bitset<32> ch = xorBitsets(andForBitset(h_bits[4], h_bits[5]), andForBitset(flipForBitset(h_bits[4]), h_bits[6]));

        std::bitset<32> temp1 = std::bitset<32>(h_bits[7].to_ulong() + s1.to_ulong() + ch.to_ulong() + k[i] + w[i].to_ulong());

        std::bitset<32> s0 = xorBitsetsTriple(rightRotate(h_bits[0], 2), rightRotate(h_bits[0], 13), rightRotate(h_bits[0], 22));

        std::bitset<32> maj = xorBitsetsTriple(andForBitset(h_bits[0], h_bits[1]), andForBitset(h_bits[0], h_bits[2]), andForBitset(h_bits[2], h_bits[1]));

        std::bitset<32> temp2 = std::bitset<32>(s0.to_ulong() + maj.to_ulong());

        for (int j = 7; j > -1; j--) {
            if (j == 0) {
                h_bits[0] = std::bitset<32>(temp1.to_ulong() + temp2.to_ulong());
            }
            else if (j == 4) {
                h_bits[4] = std::bitset<32>(h_bits[4].to_ulong() + temp1.to_ulong());
            }
            else {
                h_bits[j] = h_bits[j - 1];
            }
        }

        h_bits[4] = std::bitset<32>(h_bits[4].to_ulong() + temp1.to_ulong());


    }
    std::string res = "";
    std::bitset<32> temp_bs;
    for (int i = 0; i < 8; i++) {
        temp_bs = std::bitset<32>(std::bitset<32>(h[i]).to_ulong() + h_bits[i].to_ulong());
        res += bitsetToHexString(temp_bs);
    }

    return res;
}