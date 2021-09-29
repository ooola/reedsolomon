
#include <stdio.h>
#include <stdlib.h>
#include "galois.h"

/**
 * The number of elements in the field.dfs
 * kkk
 */

static int FIELD_SIZE = 256;

/**
 * The polynomial used to generate the logarithm table.
 *
 * There are a number of polynomials that work to generate
 * a Galois field of 256 elements.  The choice is arbitrary,
 * and we just use the first one.
 *
 * The possibilities are: 29, 43, 45, 77, 95, 99, 101, 105,
 * 113, 135, 141, 169, 195, 207, 231, and 245.
 */

static int GENERATING_POLYNOMIAL = 29;

/**
 * Mapping from members of the Galois Field to their
 * integer logarithms.  The entry for 0 is meaningless
 * because there is no log of 0.
 *
 * This array is shorts, not BYTEs, so that they can
 * be used directly to index arrays without casting.
 * The values (except the non-value at index 0) are
 * all really BYTEs, so they range from 0 to 255.
 *
 * This table was generated by java_tables.py, and the
 * unit tests check it against the Java implementation.
 */

//        -1,    0,    1,   25,    2,   50,   26,  198,
BYTE LOG_TABLE[256] = {
        0,    0,    1,   25,    2,   50,   26,  198,
        3,  223,   51,  238,   27,  104,  199,   75,
        4,  100,  224,   14,   52,  141,  239,  129,
        28,  193,  105,  248,  200,    8,   76,  113,
        5,  138,  101,   47,  225,   36,   15,   33,
        53,  147,  142,  218,  240,   18,  130,   69,
        29,  181,  194,  125,  106,   39,  249,  185,
        201,  154,    9,  120,   77,  228,  114,  166,
        6,  191,  139,   98,  102,  221,   48,  253,
        226,  152,   37,  179,   16,  145,   34,  136,
        54,  208,  148,  206,  143,  150,  219,  189,
        241,  210,   19,   92,  131,   56,   70,   64,
        30,   66,  182,  163,  195,   72,  126,  110,
        107,   58,   40,   84,  250,  133,  186,   61,
        202,   94,  155,  159,   10,   21,  121,   43,
        78,  212,  229,  172,  115,  243,  167,   87,
        7,  112,  192,  247,  140,  128,   99,   13,
        103,   74,  222,  237,   49,  197,  254,   24,
        227,  165,  153,  119,   38,  184,  180,  124,
        17,   68,  146,  217,   35,   32,  137,   46,
        55,   63,  209,   91,  149,  188,  207,  205,
        144,  135,  151,  178,  220,  252,  190,   97,
        242,   86,  211,  171,   20,   42,   93,  158,
        132,   60,   57,   83,   71,  109,   65,  162,
        31,   45,   67,  216,  183,  123,  164,  118,
        196,   23,   73,  236,  127,   12,  111,  246,
        108,  161,   59,   82,   41,  157,   85,  170,
        251,   96,  134,  177,  187,  204,   62,   90,
        203,   89,   95,  176,  156,  169,  160,   81,
        11,  245,   22,  235,  122,  117,   44,  215,
        79,  174,  213,  233,  230,  231,  173,  232,
        116,  214,  244,  234,  168,   80,   88,  175
};

BYTE *getLogTable() {
    return LOG_TABLE;
}

/**
 * Inverse of the logarithm table.  Maps integer logarithms
 * to members of the field.  There is no entry for 255
 * because the highest log is 254.
 *
 * This table was generated by java_tables.py.
 */

static BYTE EXP_TABLE[512] = {
    0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd,
    0x87, 0x13, 0x26, 0x4c, 0x98, 0x2d, 0x5a, 0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x3,
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0x9d, 0x27, 0x4e, 0x9c, 0x25, 0x4a, 0x94,
    0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee, 0xc1, 0x9f, 0x23, 0x46, 0x8c, 0x5, 0xa,
    0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba, 0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1,
    0x5f, 0xbe, 0x61, 0xc2, 0x99, 0x2f, 0x5e, 0xbc, 0x65, 0xca, 0x89, 0xf, 0x1e,
    0x3c, 0x78, 0xf0, 0xfd, 0xe7, 0xd3, 0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe,
    0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71, 0xe2, 0xd9, 0xaf, 0x43, 0x86, 0x11,
    0x22, 0x44, 0x88, 0xd, 0x1a, 0x34, 0x68, 0xd0, 0xbd, 0x67, 0xce, 0x81, 0x1f,
    0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93, 0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33,
    0x66, 0xcc, 0x85, 0x17, 0x2e, 0x5c, 0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e,
    0x21, 0x42, 0x84, 0x15, 0x2a, 0x54, 0xa8, 0x4d, 0x9a, 0x29, 0x52, 0xa4,
    0x55, 0xaa, 0x49, 0x92, 0x39, 0x72, 0xe4, 0xd5, 0xb7, 0x73, 0xe6, 0xd1,
    0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e, 0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6,
    0xf1, 0xff, 0xe3, 0xdb, 0xab, 0x4b, 0x96, 0x31, 0x62, 0xc4, 0x95, 0x37,
    0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41, 0x82, 0x19, 0x32, 0x64, 0xc8, 0x8d, 0x7,
    0xe, 0x1c, 0x38, 0x70, 0xe0, 0xdd, 0xa7, 0x53, 0xa6, 0x51, 0xa2, 0x59, 0xb2,
    0x79, 0xf2, 0xf9, 0xef, 0xc3, 0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x9, 0x12,
    0x24, 0x48, 0x90, 0x3d, 0x7a, 0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb,
    0x8b, 0xb, 0x16, 0x2c, 0x58, 0xb0, 0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36,
    0x6c, 0xd8, 0xad, 0x47, 0x8e, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,
    0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26, 0x4c, 0x98, 0x2d, 0x5a,
    0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x3, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0x9d,
    0x27, 0x4e, 0x9c, 0x25, 0x4a, 0x94, 0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee,
    0xc1, 0x9f, 0x23, 0x46, 0x8c, 0x5, 0xa, 0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba,
    0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1, 0x5f, 0xbe, 0x61, 0xc2, 0x99, 0x2f,
    0x5e, 0xbc, 0x65, 0xca, 0x89, 0xf, 0x1e, 0x3c, 0x78, 0xf0, 0xfd, 0xe7, 0xd3,
    0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe, 0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71,
    0xe2, 0xd9, 0xaf, 0x43, 0x86, 0x11, 0x22, 0x44, 0x88, 0xd, 0x1a, 0x34, 0x68,
    0xd0, 0xbd, 0x67, 0xce, 0x81, 0x1f, 0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93,
    0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33, 0x66, 0xcc, 0x85, 0x17, 0x2e, 0x5c,
    0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e, 0x21, 0x42, 0x84, 0x15, 0x2a, 0x54,
    0xa8, 0x4d, 0x9a, 0x29, 0x52, 0xa4, 0x55, 0xaa, 0x49, 0x92, 0x39, 0x72,
    0xe4, 0xd5, 0xb7, 0x73, 0xe6, 0xd1, 0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e,
    0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6, 0xf1, 0xff, 0xe3, 0xdb, 0xab, 0x4b,
    0x96, 0x31, 0x62, 0xc4, 0x95, 0x37, 0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41,
    0x82, 0x19, 0x32, 0x64, 0xc8, 0x8d, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xdd,
    0xa7, 0x53, 0xa6, 0x51, 0xa2, 0x59, 0xb2, 0x79, 0xf2, 0xf9, 0xef, 0xc3,
    0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x9, 0x12, 0x24, 0x48, 0x90, 0x3d, 0x7a,
    0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb, 0x8b, 0xb, 0x16, 0x2c, 0x58, 0xb0,
    0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36, 0x6c, 0xd8, 0xad, 0x47, 0x8e};


/*
static BYTE ORG_EXP_TABLE[512] = {
        1,    2,    4,    8,   16,   32,   64, -128,
        29,   58,  116,  -24,  -51, -121,   19,   38,
        76, -104,   45,   90,  -76,  117,  -22,  -55,
        -113,    3,    6,   12,   24,   48,   96,  -64,
        -99,   39,   78, -100,   37,   74, -108,   53,
        106,  -44,  -75,  119,  -18,  -63,  -97,   35,
        70, -116,    5,   10,   20,   40,   80,  -96,
        93,  -70,  105,  -46,  -71,  111,  -34,  -95,
        95,  -66,   97,  -62, -103,   47,   94,  -68,
        101,  -54, -119,   15,   30,   60,  120,  -16,
        -3,  -25,  -45,  -69,  107,  -42,  -79,  127,
        -2,  -31,  -33,  -93,   91,  -74,  113,  -30,
        -39,  -81,   67, -122,   17,   34,   68, -120,
        13,   26,   52,  104,  -48,  -67,  103,  -50,
        -127,   31,   62,  124,   -8,  -19,  -57, -109,
        59,  118,  -20,  -59, -105,   51,  102,  -52,
        -123,   23,   46,   92,  -72,  109,  -38,  -87,
        79,  -98,   33,   66, -124,   21,   42,   84,
        -88,   77, -102,   41,   82,  -92,   85,  -86,
        73, -110,   57,  114,  -28,  -43,  -73,  115,
        -26,  -47,  -65,   99,  -58, -111,   63,  126,
        -4,  -27,  -41,  -77,  123,  -10,  -15,   -1,
        -29,  -37,  -85,   75, -106,   49,   98,  -60,
        -107,   55,  110,  -36,  -91,   87,  -82,   65,
        -126,   25,   50,  100,  -56, -115,    7,   14,
        28,   56,  112,  -32,  -35,  -89,   83,  -90,
        81,  -94,   89,  -78,  121,  -14,   -7,  -17,
        -61, -101,   43,   86,  -84,   69, -118,    9,
        18,   36,   72, -112,   61,  122,  -12,  -11,
        -9,  -13,   -5,  -21,  -53, -117,   11,   22,
        44,   88,  -80,  125,   -6,  -23,  -49, -125,
        27,   54,  108,  -40,  -83,   71, -114,
        1,    2,    4,    8,   16,   32,   64, -128,
        29,   58,  116,  -24,  -51, -121,   19,   38,
        76, -104,   45,   90,  -76,  117,  -22,  -55,
        -113,    3,    6,   12,   24,   48,   96,  -64,
        -99,   39,   78, -100,   37,   74, -108,   53,
        106,  -44,  -75,  119,  -18,  -63,  -97,   35,
        70, -116,    5,   10,   20,   40,   80,  -96,
        93,  -70,  105,  -46,  -71,  111,  -34,  -95,
        95,  -66,   97,  -62, -103,   47,   94,  -68,
        101,  -54, -119,   15,   30,   60,  120,  -16,
        -3,  -25,  -45,  -69,  107,  -42,  -79,  127,
        -2,  -31,  -33,  -93,   91,  -74,  113,  -30,
        -39,  -81,   67, -122,   17,   34,   68, -120,
        13,   26,   52,  104,  -48,  -67,  103,  -50,
        -127,   31,   62,  124,   -8,  -19,  -57, -109,
        59,  118,  -20,  -59, -105,   51,  102,  -52,
        -123,   23,   46,   92,  -72,  109,  -38,  -87,
        79,  -98,   33,   66, -124,   21,   42,   84,
        -88,   77, -102,   41,   82,  -92,   85,  -86,
        73, -110,   57,  114,  -28,  -43,  -73,  115,
        -26,  -47,  -65,   99,  -58, -111,   63,  126,
        -4,  -27,  -41,  -77,  123,  -10,  -15,   -1,
        -29,  -37,  -85,   75, -106,   49,   98,  -60,
        -107,   55,  110,  -36,  -91,   87,  -82,   65,
        -126,   25,   50,  100,  -56, -115,    7,   14,
        28,   56,  112,  -32,  -35,  -89,   83,  -90,
        81,  -94,   89,  -78,  121,  -14,   -7,  -17,
        -61, -101,   43,   86,  -84,   69, -118,    9,
        18,   36,   72, -112,   61,  122,  -12,  -11,
        -9,  -13,   -5,  -21,  -53, -117,   11,   22,
        44,   88,  -80,  125,   -6,  -23,  -49, -125,
        27,   54,  108,  -40,  -83,   71, -114
};
*/

/**
 * A multiplication table for the Galois field.
 *
 * Using this table is an alternative to using the multiply() method,
 * which uses log/exp table lookups.
 */
BYTE* MULTIPLICATION_TABLE;

/**
 * initializes the mutliplication table
 */
void galois_init() {
    MULTIPLICATION_TABLE = generateMultiplicationTable();
}

/**
 * Adds two elements of the field.  If you're in an inner loop,
 * you should inline this function: it's just XOR.
 */
BYTE add(BYTE a, BYTE b) {
    return (BYTE) (a ^ b);
}

/**
 * Inverse of addition.  If you're in an inner loop,
 * you should inline this function: it's just XOR.
 */
BYTE subtract(BYTE a, BYTE b) {
    return (BYTE) (a ^ b);
}

/**
 * Multiplies two elements of the field.
 */
BYTE multiply(BYTE a, BYTE b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    else {
        int logA = LOG_TABLE[a & 0xFF];
        int logB = LOG_TABLE[b & 0xFF];
        int logResult = logA + logB;
        return EXP_TABLE[logResult];
    }
}

/**
 * Inverse of multiplication.
 */
BYTE divide(BYTE a, BYTE b) {
    if (a == 0) {
        return 0;
    }
    if (b == 0) {
        fprintf(stderr, "Argument 'divisor' is 0");
        exit(1);
    }
    int logA = LOG_TABLE[a & 0xFF];
    int logB = LOG_TABLE[b & 0xFF];
    int logResult = logA - logB;
    if (logResult < 0) {
        logResult += 255;
    }
    return EXP_TABLE[logResult];
}

/**
 * Computes a**n.
 *
 * The result will be the same as multiplying a times itself n times.
 *
 * @param a A member of the field.
 * @param n A plain-old integer.
 * @return The result of multiplying a by itself n times.
 */
BYTE exp(BYTE a, int n) {
    if (n == 0) {
        return 1;
    }
    else if (a == 0) {
        return 0;
    }
    else {
        int logA = LOG_TABLE[a & 0xFF];
        int logResult = logA * n;
        while (255 <= logResult) {
            logResult -= 255;
        }
        return EXP_TABLE[logResult];
    }
}

/**
 * Generates a logarithm table given a starting polynomial.
 */
int16_t* generateLogTable(int polynomial) {
    int16_t* result = (int16_t *) calloc(FIELD_SIZE, 1);
    if (!result) {
        fprintf(stderr, "calloc() failed");
        exit(1);
    }
    for (int i = 0; i < FIELD_SIZE; i++) {
        result[i] = -1; // -1 means "not set"
    }
    int b = 1;
    for (int log = 0; log < FIELD_SIZE - 1; log++) {
        if (result[b] != -1) {
            fprintf(stderr, "BUG: duplicate logarithm (bad polynomial?)");
            exit(1);
        }
        result[b] = (short) log;
        b = (b << 1);
        if (FIELD_SIZE <= b) {
            b = ((b - FIELD_SIZE) ^ polynomial);
        }
    }
    return result;
}

/**
 * Generates the inverse log table.
 */
BYTE* generateExpTable(int16_t* logTable) {
    size_t data_size = (FIELD_SIZE * 2) - 2;
    BYTE* result = (BYTE *) calloc(data_size, 1);
    if (!result) {
        fprintf(stderr, "calloc failure");
        exit(1);
    }
    for (int i = 1; i < FIELD_SIZE; i++) {
        int log = logTable[i];
        result[log] = (BYTE) i;
        result[log + FIELD_SIZE - 1] = (BYTE) i;
    }
    return result;
}

/**
 * Generates a multiplication table as an array of BYTE arrays.
 *
 * To get the result of multiplying a and b:
 *
 *     MULTIPLICATION_TABLE[a][b]
 */
BYTE* generateMultiplicationTable() {
    BYTE *result = (BYTE *) calloc(65536, 1); // 256*256 = 65536
    if (result == NULL) {
        fprintf(stderr, "malloc failure");
        exit(1);
    }
    for (int a = 0; a < FIELD_SIZE; a++) {
        for (int b = 0; b < FIELD_SIZE; b++) {
            int offset = FIELD_SIZE * a;
            result[offset] = (BYTE) multiply((BYTE) a, (BYTE) b);
        }
    }
    return result;
}