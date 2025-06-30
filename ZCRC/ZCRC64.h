/**
 * \brief utility to calculate CRC64
 * \author dovezp (github.com/dovezp)
 * \version 23/MAY/2025
 * \license Apache License 2.0
 */

#ifndef ZCRC64_H
#define ZCRC64_H

#pragma once

#include "ZCRCTables.h"

namespace utilities
{
	namespace zcrc
	{
		namespace crc64
		{
			namespace ram
			{
				/**
				 * \brief generate crc64 table then calculate crc64 through loop iterations
				 * \param data value to hash
				 * \param length size of value
				 * \return crc64 hash
				 */
				inline unsigned __int64 calculate(void* data, unsigned __int32 length)
				{
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					const unsigned __int32 crc_table_length = 256;
					unsigned __int64 crc_table[crc_table_length];
					unsigned __int64 crc = 0;

					unsigned __int32 i = 0;

					for (i = 0; i < crc_table_length; i++)
					{
						crc = i;

						for (unsigned __int8 j = 0; j < 8; j++)
						{
							crc = crc & 1 ? (crc >> 1) ^ 0x95AC9329AC4BC9B5ULL : crc >> 1;
						}

						crc_table[i] = crc;
					}

					crc = 0xFFFFFFFFFFFFFFFFULL;

					for (i = 0; i < length; i++)
					{
						crc = crc_table[(static_cast<unsigned __int8>(crc) ^ formatted_data[i]) & 0xFF] ^ (crc >> 8);
					}

					return crc;
				}
			}

			namespace rom
			{
				/**
				 * \brief calculate crc64 through loop iterations with existing table
				 * \param data value to hash
				 * \param length size of value
				 * \return crc64 hash
				 */
				inline unsigned __int64 calculate(void* data, unsigned __int32 length)
				{
					unsigned __int64 crc = 0xFFFFFFFFFFFFFFFFULL;
					auto* formatted_data = static_cast<unsigned __int8*>(data);

					for (unsigned __int32 i = 0; i < length; ++i)
					{
						crc = tables::crc_64[(static_cast<unsigned __int8>(crc) ^ formatted_data[i]) & 0xFF] ^ (crc >> 8);
					}
					return crc;
				}

				namespace meta
				{
					/**
					 * \brief recursive constexpr crc64 generator using existing table
					 * \param crc hash
					 * \param s string to iterate
					 * \return crc64 hash
					 */
					constexpr unsigned __int64 __crc64(unsigned __int64 crc, const char* s)
					{
						return *s == 0 ? crc : __crc64(tables::crc_64[(static_cast<unsigned __int8>(crc) ^ *s) & 0xFF] ^ (crc >> 8), s + 1);
					}

					/**
					 * \brief obtain crc64 with minimal meta recursive; default crc seed already set
					 * \param s string to hash
					 * \return crc64 hash
					 */
					constexpr unsigned __int64 calculate(const char* s)
					{
						return __crc64(0xFFFFFFFFFFFFFFFFULL, s);
					}
				}

				namespace tpl
				{
					/**
					 * \brief structure template format for compile time array -> crc
					 * \tparam CRC hash
					 * \tparam Characters array of characters
					 */
					template<unsigned __int64 CRC, char ...Characters>
					struct __CRC64_t {};

					/**
					 * \brief recursive compile time crc hash
					 * \tparam CRC hash
					 * \tparam Head iterate each character index
					 * \tparam Tail remaining characters
					 */
					template<unsigned __int64 CRC, char Head, char ...Tail>
					struct __CRC64_t<CRC, Head, Tail...>
					{
						static constexpr unsigned __int64 value = __CRC64_t<tables::crc_64[(static_cast<unsigned __int8>(CRC) ^ Head) & 0xFF] ^ (CRC >> 8), Tail...>::value;
					};

					/**
					 * \brief obtain final crc value
					 * \tparam CRC final crc value to return
					 */
					template<unsigned __int64 CRC>
					struct __CRC64_t<CRC>
					{
						static constexpr unsigned __int64 value = CRC;
					};

					/**
					 * \brief obtain crc64 value on compile time (example: crc64::rom::tpl::calculate<'a', 'z'>::value)
					 * \tparam Characters template array of characters to hash
					 */
					template<char ...Characters>
					using calculate = __CRC64_t<0xFFFFFFFFFFFFFFFFULL, Characters...>;
				}
			}
		}
	}
}

#endif
