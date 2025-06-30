/**
 * \brief utility to calculate CRC16
 * \author dovezp (github.com/dovezp)
 * \version 23/MAY/2025
 * \license Apache License 2.0
 */

#ifndef ZCRC16_H
#define ZCRC16_H

#pragma once

#include "ZCRCTables.h"

namespace utilities
{
	namespace zcrc
	{
		namespace crc16
		{
			namespace ram
			{
				/**
				 * \brief generate crc16 table then calculate crc16 through loop iterations
				 * \param data value to hash
				 * \param length size of value
				 * \return crc16 hash
				 */
				inline unsigned __int16 calculate(void* data, unsigned __int32 length)
				{
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					const unsigned __int32 crc_table_length = 256;
					unsigned __int16 crc_table[crc_table_length];

					unsigned __int16 crc = 0;

					unsigned __int32 i = 0;

					for (i = 0; i < crc_table_length; i++)
					{
						crc = i << 8;

						for (unsigned __int8 j = 0; j < 8; j++)
						{
							crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
						}

						crc_table[i] = crc;
					}

					crc = 0xFFFF;

					for (i = 0; i < length; i++)
					{
						crc = ((crc << 8) & 0xFFFF) ^ crc_table[(crc >> 8) ^ (formatted_data[i] & 0xFF)];
					}

					return crc;
				}
			}

			namespace rom
			{
				/**
				 * \brief calculate crc16 through loop iterations with existing table
				 * \param data value to hash
				 * \param length size of value
				 * \return crc16 hash
				 */
				inline unsigned __int16 calculate(void* data, unsigned __int32 length)
				{
					unsigned __int16 crc = 0xFFFF;
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					for (unsigned __int32 i = 0; i < length; i++)
					{
						crc = ((crc << 8) & 0xFFFF) ^ tables::crc_16[(crc >> 8) ^ (formatted_data[i] & 0xFF)];
					}
					return crc;
				}

				namespace meta
				{
					/**
					 * \brief recursive constexpr crc16 generator using existing table
					 * \param crc hash
					 * \param s string to iterate
					 * \return crc16 hash
					 */
					constexpr unsigned __int16 __crc16(unsigned __int16 crc, const char* s)
					{
						return (*s == 0) ? crc : __crc16(((crc << 8) & 0xFFFF) ^ tables::crc_16[(crc >> 8) ^ *s & 0xFF], s + 1);
					}

					/**
					 * \brief obtain crc16 with minimal meta recursive; default crc seed already set
					 * \param s string to hash
					 * \return crc16 hash
					 */
					constexpr unsigned __int16 calculate(const char* s)
					{
						return __crc16(0xFFFF, s);
					}
				}

				namespace tpl
				{
					/**
					 * \brief structure template format for compile time array -> crc
					 * \tparam CRC hash
					 * \tparam Characters array of characters
					 */
					template<unsigned __int16 CRC, char ...Characters>
					struct __CRC16_t {};

					/**
					 * \brief recursive compile time crc hash
					 * \tparam CRC hash
					 * \tparam Head iterate each character index
					 * \tparam Tail remaining characters
					 */
					template<unsigned __int16 CRC, char Head, char ...Tail>
					struct __CRC16_t<CRC, Head, Tail...>
					{
						static constexpr unsigned __int16 value = __CRC16_t<((CRC << 8) & 0xFFFF) ^ tables::crc_16[static_cast<unsigned char>(CRC >> 8) ^ static_cast<unsigned char>(Head & 0xFF)], Tail...>::value;
					};

					/**
					 * \brief obtain final crc value
					 * \tparam CRC final crc value to return
					 */
					template<unsigned __int16 CRC>
					struct __CRC16_t<CRC>
					{
						static constexpr unsigned __int16 value = CRC;
					};

					/**
					 * \brief obtain crc16 value on compile time (example: crc16::rom::tpl::calculate<'a', 'z'>::value)
					 * \tparam Characters template array of characters to hash
					 */
					template<char ...Characters>
					using calculate = __CRC16_t<0xFFFF, Characters...>;
				}
			}
		}
	}
}

#endif