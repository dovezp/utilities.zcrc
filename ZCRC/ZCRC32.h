/**
 * \brief utility to calculate CRC32
 * \author dovezp (github.com/dovezp)
 * \version 23/MAY/2025
 * \license Apache License 2.0
 */

#ifndef ZCRC32_H
#define ZCRC32_H

#pragma once

#include "ZCRCTables.h"

namespace utilities
{
	namespace zcrc
	{
		namespace crc32
		{
			namespace ram
			{
				/**
				 * \brief generate crc32 table then calculate crc32 through loop iterations
				 * \param data value to hash
				 * \param length size of value
				 * \return crc32 hash
				 */
				inline unsigned __int32 calculate(void* data, unsigned __int32 length)
				{
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					const unsigned __int32 crc_table_length = 256;
					unsigned __int32 crc_table[crc_table_length];
					unsigned __int32 crc = 0;

					unsigned __int32 i = 0;

					for (i = 0; i < crc_table_length; i++)
					{
						crc = i;

						for (unsigned __int8 j = 0; j < 8; j++)
						{
							crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320 : crc >> 1;
						}

						crc_table[i] = crc;
					}

					crc = 0xFFFFFFFF;

					for (i = 0; i < length; i++)
					{
						crc = crc_table[(crc ^ formatted_data[i]) & 0xFF] ^ (crc >> 8);
					}

					// bitwise not
					return ~crc;
				}
			}

			namespace rom
			{
				/**
				 * \brief calculate crc32 through loop iterations with existing table
				 * \param data value to hash
				 * \param length size of value
				 * \return crc32 hash
				 */
				inline unsigned __int32 calculate(void* data, unsigned __int32 length)
				{
					unsigned __int32 crc = 0xFFFFFFFF;
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					for (unsigned __int32 i = 0; i < length; ++i)
					{
						crc = ((crc >> 8) & 0x00FFFFFF) ^ tables::crc_32[(crc ^ static_cast<unsigned __int32>(*formatted_data++)) & 0xFF];
					}
					return (crc ^ 0xFFFFFFFF);
				}

				namespace meta
				{
					/**
					 * \brief recursive constexpr crc32 generator using existing table
					 * \param crc hash
					 * \param s string to iterate
					 * \return crc32 hash
					 */
					constexpr unsigned __int32 __crc32(unsigned __int32 crc, const char* s)
					{
						return *s == 0 ? crc ^ 0xFFFFFFFF : __crc32(((crc >> 8) & 0x00FFFFFF) ^ tables::crc_32[static_cast<unsigned __int8>(crc) ^ *s & 0xFF], s + 1);
					}

					/**
					 * \brief obtain crc32 with minimal meta recursive; default crc seed already set
					 * \param s string to hash
					 * \return crc32 hash
					 */
					constexpr unsigned __int32 calculate(const char* s)
					{
						return __crc32(0xFFFFFFFF, s);
					}
				}

				namespace tpl
				{
					/**
					 * \brief structure template format for compile time array -> crc
					 * \tparam CRC hash
					 * \tparam Characters array of characters
					 */
					template<unsigned __int32 CRC, char ...Characters>
					struct __CRC32_t {};

					/**
					 * \brief recursive compile time crc hash
					 * \tparam CRC hash
					 * \tparam Head iterate each character index
					 * \tparam Tail remaining characters
					 */
					template<unsigned __int32 CRC, char Head, char ...Tail>
					struct __CRC32_t<CRC, Head, Tail...>
					{
						static constexpr unsigned __int32 value = __CRC32_t<tables::crc_32[static_cast<unsigned char>(CRC) ^ static_cast<unsigned char>(Head)] ^ (CRC >> 8), Tail...>::value;
					};

					/**
					 * \brief obtain final crc value
					 * \tparam CRC final crc value to xor and return
					 */
					template<unsigned __int32 CRC>
					struct __CRC32_t<CRC>
					{
						static constexpr unsigned __int32 value = CRC ^ 0xFFFFFFFF;
					};

					/**
					 * \brief obtain crc32 value on compile time (example: crc32::rom::tpl::calculate<'a', 'z'>::value)
					 * \tparam Characters template array of characters to hash
					 */
					template<char ...Characters>
					using calculate = __CRC32_t<0xFFFFFFFF, Characters...>;
				}
			}
		}
	}
}

#endif