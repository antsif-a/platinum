#include <stdint.h>

/* credit: musl */

uint16_t bswap_16(uint16_t __x)
{
	return __x<<8 | __x>>8;
}

uint32_t bswap_32(uint32_t __x)
{
	return __x>>24 | (__x>>8&0xff00) | (__x<<8&0xff0000) | __x<<24;
}

uint64_t bswap_64(uint64_t __x)
{
	return (bswap_32(__x)+0ULL)<<32 | bswap_32(__x>>32);
}
