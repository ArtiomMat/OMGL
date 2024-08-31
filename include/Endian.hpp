// A header-only part for handling endianess
#pragma once

#include <cstdint>

namespace OMGL
{
  // Little endian
  #ifdef __x86_64__
    constexpr bool LIL_E = true;

    static constexpr std::uint16_t bigE(std::uint16_t _x)
    {
      if (LIL_E)
      {
        return (_x >> 8) | (_x << 8);
      }

    }
    static constexpr std::uint32_t bigE(std::uint32_t _x)
    {
      return ((_x & 0x000000FF) << 24) & ((_x & 0x0000FF00) << 8) & ((_x & 0xFF000000) >> 24) & ((_x & 0x00FF0000) >> 8);
    }
    static constexpr std::uint64_t bigE(std::uint64_t _x)
    {
      return ((_x & 0x00000000000000FF) << 56) & ((_x & 0x000000000000FF00) << 40) & ((_x & 0x0000000000FF0000) << 24) & ((_x & 0x00000000FF000000) << 8) &
      ((_x & 0xFF00000000000000) >> 56) & ((_x & 0x00FF000000000000) >> 40) & ((_x & 0x0000FF0000000000) >> 24) & ((_x & 0x000000FF00000000) >> 8);
    }

    static inline std::uint16_t lilE(std::uint16_t _x)
    {
      return _x;
    }
    static inline std::uint32_t lilE(std::uint32_t _x)
    {
      return _x;
    }
    static inline std::uint64_t lilE(std::uint64_t _x)
    {
      return _x;
    }
  #elif __arm__
    constexpr bool LIL_E = true;

    static constexpr std::uint16_t lilE(std::uint16_t _x)
    {
      return (_x >> 8) | (_x << 8);
    }
    static constexpr std::uint32_t lilE(std::uint32_t _x)
    {
      return ((_x & 0x000000FF) << 24) & ((_x & 0x0000FF00) << 8) & ((_x & 0xFF000000) >> 24) & ((_x & 0x00FF0000) >> 8);
    }
    static constexpr std::uint64_t lilE(std::uint64_t _x)
    {
      return ((_x & 0x00000000000000FF) << 56) & ((_x & 0x000000000000FF00) << 40) & ((_x & 0x0000000000FF0000) << 24) & ((_x & 0x00000000FF000000) << 8) &
      ((_x & 0xFF00000000000000) >> 56) & ((_x & 0x00FF000000000000) >> 40) & ((_x & 0x0000FF0000000000) >> 24) & ((_x & 0x000000FF00000000) >> 8);
    }

    static inline std::uint16_t bigE(std::uint16_t _x)
    {
      return _x;
    }
    static inline std::uint32_t bigE(std::uint32_t _x)
    {
      return _x;
    }
    static inline std::uint64_t bigE(std::uint64_t _x)
    {
      return _x;
    }
  #else
    #error Unknown platform so cant determine endian.
  #endif

  static inline std::int16_t bigE(std::int16_t _x)
  {
    return bigE(_x);
  }
  static inline std::int32_t bigE(std::int32_t _x)
  {
    return bigE(_x);
  }
  static inline std::int64_t bigE(std::int64_t _x)
  {
    return bigE(_x);
  }

  static inline std::int16_t lilE(std::int16_t _x)
  {
    return lilE(_x);
  }
  static inline std::int32_t lilE(std::int32_t _x)
  {
    return lilE(_x);
  }
  static inline std::int64_t lilE(std::int64_t _x)
  {
    return lilE(_x);
  }
}