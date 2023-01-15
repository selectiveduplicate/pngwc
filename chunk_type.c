#include <stdlib.h>
#include <ctype.h>

#include "chunk_type.h"

/* 
 * Returns a printable error string. 
 */
const char* 
chunktype_error_str(chunk_type_error_t err)
{
	const char* err_str = NULL;

	// Check if error code is out of range
	if (err > CHUNKTYPE_ERROR_COUNT) return err_str;

	err_str = CHUNKTYPE_ERROR_STRS[err];
	return err_str;
}

/* 
 * Array of strings to map enum error types to 
 * printable strings
 */
const char* const CHUNKTYPE_ERROR_STRS[2] = 
{
	"CHUNKTYPE_ERROR_OK",
	"CHUNKTYPE_ERROR_NON_ALPHABETIC_ASCII",
};

/* 
 * Returns the non-alphabetic error code. 
 */
chunk_type_error_t 
chunk_type_error_non_alphabetic_ascii(void)
{
	return CHUNKTYPE_ERROR_NON_ALPHABETIC_ASCII;
}

/* 
 *Returns ok error code so no error. 
 */
chunk_type_error_t 
chunk_type_error_ok(void)
{
	return CHUNKTYPE_ERROR_OK;
}

/*
 * Creates a chunk type from an array of four bytes.
 * Returns printable `CHUNKTYPE_ERROR_OK` string upon success 
 * and the created chunk type via the output parameter `ct`.
 */
const char* 
chunk_type_from_bytes(unsigned char s[], struct chunk_type* ct)
{
	for (size_t i = 0; i < 4; i++) {
		if (!isalpha(s[i])) {
			return chunktype_error_str(
		    	    chunk_type_error_non_alphabetic_ascii()
		    	);
		}
		ct->chunk_type[i] = s[i];
	}

	return chunktype_error_str(chunk_type_error_ok());
}

/*
 * Creates a chunk type from a string.
 * Returns printable `CHUNKTYPE_ERROR_OK` string upon success 
 * and the created chunk type via the output parameter `ct`.
 */
const char* 
chunk_type_from_str(const char* s, struct chunk_type* ct)
{
	for (size_t i = 0; i < 4; i++) {
		if (!isalpha(s[i]))
			return chunktype_error_str(
		    	    chunk_type_error_non_alphabetic_ascii()
		    	);
		ct->chunk_type[i] = s[i];
	}

	return chunktype_error_str(chunk_type_error_ok());

}

/*
 * Returns true if chunk type is critical.
 * Critical chunk type has the 5th bit of the 1st byte set to 0, 
 * meaning uppercase.
*/
bool
chunk_type_is_critical(struct chunk_type* ct)
{
	unsigned char first_byte = ct->chunk_type[0];
	
	/* Shift the bits five positions to the right 
	 * to get the fifth bit. Use AND mask to check 
	 * if the bit is set (lowercase, ancillary) or 
	 * not (uppercase, critical).
	 */
	if (((first_byte >> 5) & 1) != 0)
		return false;
	return true;
}

/*
 * Returns true if chunk type is public.
 * Public chunk type has the 5th bit of the 2nd byte set to 0, 
 * meaning uppercase.
*/
bool
chunk_type_is_public(struct chunk_type* ct)
{
	unsigned char second_byte = ct->chunk_type[1];

	if (((second_byte >> 5) & 1) == 0)
		return true;
	return false;
}