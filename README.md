# ZCRC - High-Performance CRC Calculation Library

## About

ZCRC is a high-performance CRC (Cyclic Redundancy Check) calculation library. This project serves as an excellent example of modern C++ design patterns, template metaprogramming, and performance optimization techniques.


## Performance Benchmarks

| Method | Speed | Memory | Use Case |
|--------|--------|---------|----------|
| **RAM** | 🟡 Medium | 🟢 Low | Dynamic/variable algorithms |
| **ROM** | 🟢 Fast | 🟡 Medium | Standard production use |
| **META** | 🟢 Fast | 🟢 Low | Compile-time known strings |
| **TPL** | ⚡ **Zero Cost** | 🟢 Low | Template parameters |

*Template calculations have **zero runtime overhead** - computed entirely at compile-time!*


## Quick Start

### Basic Usage

Include `ZCRC{8,16,32,64}.h` and `ZCRCTables.h` into your project.

```cpp
#include "ZCRC/ZCRC32.h"
using namespace utilities::zcrc;

// Simple runtime calculation
std::string data = "Hello, World!";
auto crc = crc32::rom::calculate(
    reinterpret_cast<const uint8_t*>(data.c_str()), 
    data.length()
);

// Compile-time calculation (zero runtime cost)
constexpr auto compile_time_crc = crc32::rom::meta::calculate("Hello, World!");

// API hashing for dynamic imports (common in security tools)
constexpr uint32_t kernel32_hash = crc32::rom::tpl::calculate<
    'k','e','r','n','e','l','3','2','.','d','l','l'>::value;
```

### Build Requirements

- **Visual Studio 2022** (v143 toolset)
- **C++17** or later
- **Windows 10 SDK**
- **Google Test** (for testing)

### Building
```cmd
# Open in Visual Studio
start Utilities.ZCRC.sln

# Or build from command line
msbuild Utilities.ZCRC.sln /p:Configuration=Release /p:Platform=x64
```

### License
This project operates under the [Apache License 2.0 (Apache-2.0)](https://tldrlegal.com/license/apache-license-2.0-(apache-2.0)). Please refer to the [LICENSE.md](./LICENSE.md) file for detailed information.

### Your Feedback Counts

Your insights and feedback, whether positive or constructive, are immensely valuable. Your contributions guide the refinement of the Codex Plugin for future iterations.

Share your thoughts by opening an issue in the [repository's issue section](https://github.com/dovezp/utilities.zcrc/issues). Be sure to provide context and links when sharing your feedback.

Thank you for being an essential part of the Codex Plugin's growth journey.

<p align="center">
  <p align="center">
    <a href="https://github.com/dovezp/utilities.zcrc/graphs/contributors">
      <img src="https://img.shields.io/github/contributors/dovezp/utilities.zcrc?style=flat-square" alt="contributors"/>
    </a>
    <a href="https://github.com/dovezp/utilities.zcrc/watchers">
      <img src="https://img.shields.io/github/watchers/dovezp/utilities.zcrc?style=flat-square" alt="watchers"/>
    </a>
    <a href="https://github.com/dovezp/utilities.zcrc/stargazers">
      <img src="https://img.shields.io/github/stars/dovezp/utilities.zcrc?style=flat-square" alt="stars"/>
    </a>
    <a href="https://github.com/dovezp/utilities.zcrc/network/members">
      <img src="https://img.shields.io/github/forks/dovezp/utilities.zcrc?style=flat-square" alt="forks"/>
    </a>
  </p>
</p>

<p align="center">
  <a href="https://github.com/dovezp">
    <img width="64" heigth="64" src="https://avatars.githubusercontent.com/u/89095890" alt="dovezp"/>
  </a>
</p>
