#ifndef UTILS_H
#define UTILS_H

#define BUFFER_SIZE(buffer) sizeof(buffer) / sizeof(buffer[0])

#define NUM_ROWS(m) \
    BUFFER_SIZE(m)

#define NUM_COLS(m) \
    BUFFER_SIZE(m[0])

#define MATRIX_SIZE(m) \
    NUM_ROWS(m) * NUM_COLS(m)


// https://stackoverflow.com/questions/2182002/how-to-convert-big-endian-to-little-endian-in-c-without-using-library-functions
#define swap_endianess_32(num)                                                                                         \
    ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000)

#endif