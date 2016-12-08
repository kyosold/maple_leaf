#ifndef __ML_STANDARD_H__
#define __ML_STANDARD_H__


/**
 * ml_base64_encode
 * Encodes data with MIME base64
 *
 * @str     The data to encode
 * @length  Length of str
 *
 * @return  The encoded data, as a string or NULL on failure
 * @notice  You must free the encoded data after at finished.
 */
char *ml_base64_encode_alloc(const unsigned char *str, size_t length);

/**
 * ml_base64_decode
 * Decodes data encoded with MIME base64
 *
 * @str     The encoded data
 * @length  Length of str
 *
 * @return  Returns the original data or NULL on failure. The returned data may be binary.
 * @notice  You must free the encoded data after at finished.
 */
char *ml_base64_decode_alloc(const unsigned char *str, size_t length);


/**
 * ml_bin2hex
 * Convert binary data into hexadecimal representation
 *
 * @indata      A string
 * @indata_len  Length of indata
 *
 * @return      Returns the hexadecimal representation of the given string.
 * @notice      You must free the return data after at finished.
 */
char *ml_bin2hex(const unsigned char *indata, const size_t indata_len);

/**
 * ml_hex2bin
 * Decodes a hexadecimally encoded binary string
 *
 * @indata      Hexadecimal representation of data
 * @indata_len  length of indata
 *
 * @return      Returns the binary representation of the given data or NULL on failure
 * @notice      You must free the return data after at finished.
 */
char *ml_hex2bin(const unsigned char *indata, const size_t indata_len);



#endif

