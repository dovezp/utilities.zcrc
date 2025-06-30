/**
 * \brief utility to calculate CRC8
 * \author dovezp (github.com/dovezp)
 * \version 23/MAY/2025
 * \license Apache License 2.0
 */

#ifndef ZCRC8_H
#define ZCRC8_H

#pragma once

#include "ZCRCTables.h"

namespace utilities
{
	namespace zcrc
	{
		namespace crc8
		{
			namespace ram
			{
				/**
				 * \brief generate crc8 table then calculate crc8 through loop iterations
				 * \param data value to hash
				 * \param length size of value
				 * \return crc8 hash
				 */
				inline unsigned __int8 calculate(void* data, unsigned __int32 length)
				{
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					const unsigned __int32 crc_table_length = 256;
					unsigned __int8 crc_table[crc_table_length];

					unsigned __int8 crc = 0;

					unsigned __int32 i = 0;

					for (i = 0; i < crc_table_length; i++)
					{
						crc = i;

						for (unsigned __int8 j = 0; j < 8; j++)
						{
							crc = (crc << 1) ^ ((crc & 0x80) ? 0x07 : 0);
						}

						crc_table[i] = crc & 0xFF;
					}

					crc = 0;

					for (i = 0; i < length; i++)
					{
						crc = crc_table[formatted_data[i] ^ crc];
					}

					return crc;
				}
			}

			namespace rom
			{
				/**
				 * \brief calculate crc8 through loop iterations with existing table
				 * \param data value to hash
				 * \param length size of value
				 * \return crc8 hash
				 */
				inline unsigned __int8 calculate(void* data, unsigned __int32 length)
				{
					unsigned __int8 crc = 0x00;
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					for (unsigned __int32 i = 0; i < length; i++)
					{
						crc = tables::crc_8[formatted_data[i] ^ crc];
					}
					return crc;
				}

				namespace meta
				{
					/**
					 * \brief recursive constexpr crc8 generator using existing table
					 * \param crc hash
					 * \param s string to iterate
					 * \return crc8 hash
					 */
					constexpr unsigned __int8 __crc8(unsigned __int8 crc, const char* s)
					{
						return (*s == 0) ? crc : __crc8(tables::crc_8[static_cast<unsigned __int8>(crc) ^ *s], s + 1);
					}

					/**
					 * \brief obtain crc8 with minimal meta recursive; default crc seed already set
					 * \param s string to hash
					 * \return crc8 hash
					 */
					constexpr unsigned __int8 calculate(const char* s)
					{
						return __crc8(0x00, s);
					}
				}

				namespace tpl
				{
					/**
					 * \brief structure template format for compile time array -> crc
					 * \tparam CRC hash
					 * \tparam Characters array of characters
					 */
					template<unsigned __int8 CRC, char ...Characters>
					struct __CRC8_t {};

					/**
					 * \brief recursive compile time crc hash
					 * \tparam CRC hash
					 * \tparam Head iterate each character index
					 * \tparam Tail remaining characters
					 */
					template<unsigned __int8 CRC, char Head, char ...Tail>
					struct __CRC8_t<CRC, Head, Tail...>
					{
						static constexpr unsigned __int8 value = __CRC8_t<tables::crc_8[CRC ^ Head], Tail...>::value;
					};

					/**
					 * \brief obtain final crc value
					 * \tparam CRC final crc value to return
					 */
					template<unsigned __int8 CRC>
					struct __CRC8_t<CRC>
					{
						static constexpr unsigned __int8 value = CRC;
					};

					/**
					 * \brief obtain crc8 value on compile time (example: crc8::rom::tpl::calculate<'a', 'z'>::value)
					 * \tparam Characters template array of characters to hash
					 */
					template<char ...Characters>
					using calculate = __CRC8_t<0x00, Characters...>;
				}
			}
		}
	}
}

#endif
