/**
 * \brief Tests for ZCRC
 * \author dovezp (github.com/dovezp)
 * \version 23/MAY/2025
 * \license Apache License 2.0
 */

#include "ZCRCTests.h"

using namespace utilities::zcrc;

// Define a test string to use across all tests
const std::string input_value = "kernel32.dll";

// Expected CRC values for "kernel32.dll"
constexpr uint8_t  EXPECTED_CRC8 = 0x48;
constexpr uint16_t EXPECTED_CRC16 = 0x4F48;
constexpr uint32_t EXPECTED_CRC32 = 0x3408A66B;
constexpr uint64_t EXPECTED_CRC64 = 0xBA0A4B4C0C4EDEC4ULL;

// CRC8 Tests
TEST(ZCRC8Test, RamCalculation) {
	uint8_t result = crc8::ram::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC8);
}

TEST(ZCRC8Test, RomCalculation) {
	uint8_t result = crc8::rom::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC8);
}

TEST(ZCRC8Test, MetaCalculation) {
	constexpr uint8_t result = crc8::rom::meta::calculate("kernel32.dll");
	EXPECT_EQ(result, EXPECTED_CRC8);
}

TEST(ZCRC8Test, TemplateCalculation) {
	constexpr uint8_t result = crc8::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(result, EXPECTED_CRC8);
}

// CRC16 Tests
TEST(ZCRC16Test, RamCalculation) {
	uint16_t result = crc16::ram::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC16);
}

TEST(ZCRC16Test, RomCalculation) {
	uint16_t result = crc16::rom::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC16);
}

TEST(ZCRC16Test, MetaCalculation) {
	constexpr uint16_t result = crc16::rom::meta::calculate("kernel32.dll");
	EXPECT_EQ(result, EXPECTED_CRC16);
}

TEST(ZCRC16Test, TemplateCalculation) {
	constexpr uint16_t result = crc16::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(result, EXPECTED_CRC16);
}

// CRC32 Tests
TEST(ZCRC32Test, RamCalculation) {
	uint32_t result = crc32::ram::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC32);
}

TEST(ZCRC32Test, RomCalculation) {
	uint32_t result = crc32::rom::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC32);
}

TEST(ZCRC32Test, MetaCalculation) {
	constexpr uint32_t result = crc32::rom::meta::calculate("kernel32.dll");
	EXPECT_EQ(result, EXPECTED_CRC32);
}

TEST(ZCRC32Test, TemplateCalculation) {
	constexpr uint32_t result = crc32::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(result, EXPECTED_CRC32);
}

// CRC64 Tests
TEST(ZCRC64Test, RamCalculation) {
	uint64_t result = crc64::ram::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC64);
}

TEST(ZCRC64Test, RomCalculation) {
	uint64_t result = crc64::ram::calculate((void*)input_value.c_str(), input_value.length());
	EXPECT_EQ(result, EXPECTED_CRC64);
}

TEST(ZCRC64Test, MetaCalculation) {
	constexpr uint64_t result = crc64::rom::meta::calculate("kernel32.dll");
	EXPECT_EQ(result, EXPECTED_CRC64);
}

TEST(ZCRC64Test, TemplateCalculation) {
	constexpr uint64_t result = crc64::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(result, EXPECTED_CRC64);
}

// Consistency Tests
TEST(ZCRCConsistencyTest, CRCImplementations) {
	// CRC8
	uint8_t crc8_ram = crc8::ram::calculate((void*)input_value.c_str(), input_value.length());
	uint8_t crc8_rom = crc8::rom::calculate((void*)input_value.c_str(), input_value.length());
	constexpr uint8_t crc8_meta = crc8::rom::meta::calculate("kernel32.dll");
	constexpr uint8_t crc8_tpl = crc8::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(crc8_ram, crc8_rom);
	EXPECT_EQ(crc8_rom, crc8_meta);
	EXPECT_EQ(crc8_meta, crc8_tpl);

	// CRC16
	uint16_t crc16_ram = crc16::ram::calculate((void*)input_value.c_str(), input_value.length());
	uint16_t crc16_rom = crc16::rom::calculate((void*)input_value.c_str(), input_value.length());
	constexpr uint16_t crc16_meta = crc16::rom::meta::calculate("kernel32.dll");
	constexpr uint16_t crc16_tpl = crc16::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(crc16_ram, crc16_rom);
	EXPECT_EQ(crc16_rom, crc16_meta);
	EXPECT_EQ(crc16_meta, crc16_tpl);

	// CRC32
	uint32_t crc32_ram = crc32::ram::calculate((void*)input_value.c_str(), input_value.length());
	uint32_t crc32_rom = crc32::rom::calculate((void*)input_value.c_str(), input_value.length());
	constexpr uint32_t crc32_meta = crc32::rom::meta::calculate("kernel32.dll");
	constexpr uint32_t crc32_tpl = crc32::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(crc32_ram, crc32_rom);
	EXPECT_EQ(crc32_rom, crc32_meta);
	EXPECT_EQ(crc32_meta, crc32_tpl);

	// CRC64
	uint64_t crc64_ram = crc64::ram::calculate((void*)input_value.c_str(), input_value.length());
	uint64_t crc64_rom = crc64::rom::calculate((void*)input_value.c_str(), input_value.length());
	constexpr uint64_t crc64_meta = crc64::rom::meta::calculate("kernel32.dll");
	constexpr uint64_t crc64_tpl = crc64::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value;
	EXPECT_EQ(crc64_ram, crc64_rom);
	EXPECT_EQ(crc64_rom, crc64_meta);
	EXPECT_EQ(crc64_meta, crc64_tpl);
}

// Edge Case Tests
TEST(ZCRCEdgeCaseTest, EmptyString) {
	const std::string empty_value = "";
	void* data = (void*)empty_value.c_str();
	uint32_t length = empty_value.length();

	EXPECT_EQ(crc8::ram::calculate(data, length), 0x00);
	EXPECT_EQ(crc16::ram::calculate(data, length), 0x0000);
	EXPECT_EQ(crc32::ram::calculate(data, length), 0x00000000);
	EXPECT_EQ(crc64::ram::calculate(data, length), 0xFFFFFFFFFFFFFFFFULL);
}