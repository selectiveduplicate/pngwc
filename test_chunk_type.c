#include <stdlib.h>
#include <assert.h>

#include "chunk_type.h"
#include "test-framework/unity.h"

void 
setUp(void)
{
}

void 
tearDown(void)
{
}

static void 
test_chunk_type_from_four_bytes(void)
{
	unsigned char b[] = {84, 101, 65, 114};
	struct chunk_type byte_ct;
	TEST_ASSERT_EQUAL_STRING(
	    "CHUNKTYPE_ERROR_OK", chunk_type_from_bytes(b, &byte_ct)
	);
	TEST_ASSERT_CHAR_ARRAY_WITHIN(0, b, byte_ct.chunk_type, 4);
}

static void 
test_chunk_type_with_non_alphbetic_byte(void)
{
	unsigned char b[] = {84, 101, 64, 114};
	struct chunk_type byte_ct;
	TEST_ASSERT_EQUAL_STRING(
	    "CHUNKTYPE_ERROR_NON_ALPHABETIC_ASCII", chunk_type_from_bytes(b, &byte_ct)
	);
}

static void 
test_chunk_type_from_str(void)
{
	struct chunk_type expected = {
		.chunk_type = {84, 101, 65, 114}
	};
	struct chunk_type actual; 
	const char* actual_result = chunk_type_from_str("TeAr", &actual);

	TEST_ASSERT_CHAR_ARRAY_WITHIN(
	    0, expected.chunk_type, actual.chunk_type, 4
	);
	TEST_ASSERT_EQUAL_STRING("CHUNKTYPE_ERROR_OK", actual_result);
}

static void 
test_chunk_type_is_critical(void)
{
	struct chunk_type ct;
	const char* result = chunk_type_from_str("TeAr", &ct);

	TEST_ASSERT_TRUE(chunk_type_is_critical(&ct));
	TEST_ASSERT_EQUAL_STRING("CHUNKTYPE_ERROR_OK", result);	
}

static void 
test_chunk_type_is_not_critical(void)
{
	struct chunk_type ct;
	const char* result = chunk_type_from_str("teAr", &ct);

	TEST_ASSERT_FALSE(chunk_type_is_critical(&ct));
	TEST_ASSERT_EQUAL_STRING("CHUNKTYPE_ERROR_OK", result);	
}

static void
test_chunk_type_is_public(void)
{
	struct chunk_type ct;
	const char* result = chunk_type_from_str("tEAr", &ct);

	TEST_ASSERT_TRUE(chunk_type_is_public(&ct));
	TEST_ASSERT_EQUAL_STRING("CHUNKTYPE_ERROR_OK", result);
}

int 
main(void)
{
	UnityBegin("test_chunk_type.c");

	RUN_TEST(test_chunk_type_from_four_bytes);
	RUN_TEST(test_chunk_type_with_non_alphbetic_byte);
	RUN_TEST(test_chunk_type_from_str);
	RUN_TEST(test_chunk_type_is_critical);
	RUN_TEST(test_chunk_type_is_not_critical);
	RUN_TEST(test_chunk_type_is_public);

	return UnityEnd();
}