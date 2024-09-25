#include "./helpers.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

std::string generate_uuid() {
  // Random number generator.
  // TODO(June): Look into this.
  std::random_device rd;
  std::mt19937 gen(rd());
  // gaussian from 0 to 2^32-1(4*8)
  std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

  // 8 hexadecimal numbers
  uint32_t part1 = dist(gen);
  // 4 numbers
  // Can bitmask as well which would be AND with 16 bits
  uint16_t part2 = static_cast<uint16_t>(dist(gen));
  // 4 numbers and ensure that first number is 4.
  // only fill 12 bits and then add 4 in the front
  uint16_t part3 = (dist(gen) & 0x0FFF) | 0x4000;
  // 4 numbers
  // ensure first is between 8, 9, a, b.
  uint16_t part4 = (dist(gen) & 0x3FFF) | 0x8000;
  // 4 numbers
  uint16_t part5 = static_cast<uint16_t>(dist(gen));
  // 8 numbers
  uint32_t part6 = dist(gen);

  // Use a stringstream to format the UUID string
  std::stringstream ss;
  ss << std::hex << std::setw(8) << part1 << "-" << std::setw(4) << part2 << "-"
     << std::setw(4) << part3 << "-" << std::setw(4) << part4
     << "-"
     // don't need - for this part
     << std::setw(4) << part5 << std::setw(8) << part6;

  return ss.str();
}
