/**
 * This implements the sample encoder
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "util.h"
#include "rs.h"

#define DATA_SHARDS 4
#define PARITY_SHARDS 2
#define TOTAL_SHARDS 6
#define BYTES_IN_INT 4 // TODO double check this on x64

/**
 * define ntohl here since byteswap.h is not available on OS X where the testing was done
 */
uint32_t myntohl(uint32_t const net)
{
    uint8_t data[4] = {};
    memcpy(&data, &net, sizeof(data));

    return ((uint32_t) data[3] << 0)
         | ((uint32_t) data[2] << 8)
         | ((uint32_t) data[1] << 16)
         | ((uint32_t) data[0] << 24);
}

/**
 * reads the whole file into the passed in buffer.
 * returns 0 if the file could not be read or the number of bytes read if successful
 */
size_t read_file(char const* filename, char* file_buffer)
{
    FILE *infile;
    long num_bytes;

    infile = fopen(filename, "r");
    if (infile == NULL) {
        return 0;
    }
    fseek(infile, 0L, SEEK_END);
    num_bytes = ftell(infile);

    fseek(infile, 0L, SEEK_SET);
    size_t bytes_read = fread(file_buffer, sizeof(char), num_bytes, infile);
    fclose(infile);
    return bytes_read;
}

/**
 * writes count bytes from buf into filename
 * exits if any errors occur
 */
void write_file(char* filename, char* buf, size_t count)
{ 
    FILE *f = NULL;

    if (!filename || !buf || count == 0) {
        fprintf(stderr, "invalid params passed to write_file(), exiting.");
        exit(1);
    }

    f = fopen(filename , "w");
    if (f == NULL) {
        fprintf(stderr, "Error opening: %s for writing, exiting.", filename);
        exit(1);
    }
    fwrite(buf, sizeof(char),  count, f);
    fclose(f);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    struct stat sb;

    if (argc != 1) {
        printf("Usage: SampleEncoder <fileName>\n");
        return 1;
    }
    printf("%s\n%s\n", argv[0], argv[1]);

    //char *file_name = argv[1];
    char const* file_name = "/Users/onordstrom/src/reedsolomon/sample-input.txt";

    if (stat(file_name, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Get the size of the input file.  (Files bigger that
    // Integer.MAX_VALUE will fail here!)
    size_t fileSize = sb.st_size;

    // Figure out how big each shard will be.  The total size stored
    // will be the file size (4 bytes) plus the file.
    int storedSize = fileSize + BYTES_IN_INT;
    int shardSize = (storedSize + DATA_SHARDS - 1) / DATA_SHARDS;

    // Create a buffer holding the file size, followed by
    // the contents of the file and the coded shards.
    int bufferSize = shardSize * TOTAL_SHARDS;
    char* file_buffer = (char*) allocate_shared_memory_or_exit((size_t)bufferSize);

    //printf("file bufferSize: %d shardSize: %d stored size: %d\n", bufferSize, shardSize, storedSize);

    // java is big endian so to be compatible with JavaReedSolomon convert the filesize to big endian
    int32_t big_endian_file_size = myntohl(fileSize);
    memcpy(file_buffer, &big_endian_file_size, BYTES_IN_INT);

    size_t bytes_read = read_file(file_name, file_buffer + BYTES_IN_INT);
    if (bytes_read != fileSize) {
        printf("unable to read whole file: %s, file_size: %lu, bytes read: %lu\n", file_name, fileSize, bytes_read);
    }

    // Use Reed-Solomon to calculate the parity.
    rs_t* reed_solomon = rs(DATA_SHARDS, PARITY_SHARDS);

    // TODO: declare  check reed
    encode_parity(reed_solomon,
                  (BYTE*)file_buffer,    // *input_ shards
                  0,              // offset
                  shardSize);    // bytes in each shard

    // Write out the resulting files.
    for (int i = 0; i < TOTAL_SHARDS; i++) {
        size_t output_filename_length = strlen(file_name) + 4;
        char* output_filename = (char *) calloc(1, output_filename_length);
        if (!output_filename) {
            fprintf(stderr, "failed to allocate memory for output file, exiting.");
            exit(1);
        }
        snprintf(output_filename, output_filename_length, "%s.%d", file_name, i);
        char *buf = file_buffer + (i * shardSize);
        write_file(output_filename, buf, shardSize);
        printf("wrote %s\n", output_filename);
    }
    return 0;
}
