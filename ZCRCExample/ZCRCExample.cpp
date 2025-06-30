/**
 * \brief example of ZCRC usage
 * \author dovezp (github.com/dovezp)
 * \version 23/MAY/2025
 * \license Apache License 2.0
 */

#include "ZCRCExample.h"

#include <string>
#include <iostream>

using namespace utilities::zcrc;

int main()
{
	const std::string input_value = "kernel32.dll";

	std::cout << "Original Value: " << input_value << std::endl << std::endl;

	//--------------------------------------------------------------------------

	std::cout << "CRC8 Calculation via 'RAM': " <<
		std::hex <<
		crc8::ram::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC8 Calculation via 'ROM': " <<
		std::hex <<
		crc8::rom::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC8 Calculation via 'META': " <<
		std::hex <<
		crc8::rom::meta::calculate(input_value.c_str()) <<
		std::endl;

	std::cout << "CRC8 Calculation via 'TPL':  " <<
		std::hex <<
		crc8::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value <<
		std::endl << std::endl;

	//--------------------------------------------------------------------------

	std::cout << "CRC16 Calculation via 'RAM': " <<
		std::hex <<
		crc16::ram::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC16 Calculation via 'ROM': " <<
		std::hex <<
		crc16::rom::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC16 Calculation via 'META': " <<
		std::hex <<
		crc16::rom::meta::calculate(input_value.c_str()) <<
		std::endl;

	std::cout << "CRC16 Calculation via 'TPL':  " <<
		std::hex <<
		crc16::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value <<
		std::endl << std::endl;

	//--------------------------------------------------------------------------

	std::cout << "CRC32 Calculation via 'RAM': " <<
		std::hex <<
		crc32::ram::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC32 Calculation via 'ROM': " <<
		std::hex <<
		crc32::rom::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC32 Calculation via 'META': " <<
		std::hex <<
		crc32::rom::meta::calculate(input_value.c_str()) <<
		std::endl;

	std::cout << "CRC32 Calculation via 'TPL':  " <<
		std::hex <<
		crc32::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value <<
		std::endl << std::endl;

	//--------------------------------------------------------------------------

	std::cout << "CRC64 Calculation via 'RAM': " <<
		std::hex <<
		crc64::ram::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC64 Calculation via 'ROM': " <<
		std::hex <<
		crc64::rom::calculate((void*)input_value.c_str(), input_value.length()) <<
		std::endl;

	std::cout << "CRC64 Calculation via 'META': " <<
		std::hex <<
		crc64::rom::meta::calculate(input_value.c_str()) <<
		std::endl;

	std::cout << "CRC64 Calculation via 'TPL':  " <<
		std::hex <<
		crc64::rom::tpl::calculate<'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l'>::value <<
		std::endl << std::endl;

	return 0;
}