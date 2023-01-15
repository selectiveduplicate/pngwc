#ifndef CHUNK_TYPE_H
#define CHUNK_TYPE_H

#include <stdbool.h>

/* 
 * A four-byte chunk type code of a PNG chunk. 
 */
struct chunk_type {
	unsigned char	chunk_type[4];
};

/*
 * Errors for chunk type.
 */
typedef enum {
	// No error
	CHUNKTYPE_ERROR_OK = 0,

	// Each bytes must be a alphabetic ASCII character.
	CHUNKTYPE_ERROR_NON_ALPHABETIC_ASCII,

	// Total number of errors in this list (NOT AN ACTUAL ERROR CODE);
	CHUNKTYPE_ERROR_COUNT,
} chunk_type_error_t;

extern const char* 	const CHUNKTYPE_ERROR_STRS[2]; 

chunk_type_error_t 	chunk_type_error_non_alphabetic_ascii(void);
chunk_type_error_t 	chunk_type_error_ok(void);
const char*		chunktype_error_str(chunk_type_error_t);
const char*		chunk_type_from_bytes(unsigned char [], struct chunk_type*);
const char*		chunk_type_from_str(const char*, struct chunk_type*);
bool			chunk_type_is_critical(struct chunk_type*);
bool			chunk_type_is_public(struct chunk_type*);

#endif