#ifndef RLE_H
#define RLE_H
int compress(const char *input, char *output);
int decompress(const char *input, char *output);
void analyze_compression(const char *original, const char *compressed);
void verify_roundtrip(const char *original, const char *decompressed);
#endif
