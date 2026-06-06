/*
 * rle_decompress.c
 * Run-Length Encoding (RLE) — Decompression
 *
 * Author : Meenakshi Mamidala
 * GitHub : github.com/meenakshi-mamidala
 *
 * Complexity:
 *   Time  : O(n)  — single pass through compressed string
 *   Space : O(m)  — output size m (decompressed length)
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rle.h"

int decompress(const char *input, char *output) {
    int i = 0, j = 0;
    int n = strlen(input);

    while (i < n) {
        int count = 0;
        while (i < n && isdigit(input[i])) {
            count = count * 10 + (input[i] - '0');
            i++;
        }
        if (count == 0) count = 1;
        if (i < n && !isdigit(input[i])) {
            char ch = input[i++];
            for (int k = 0; k < count; k++) output[j++] = ch;
        }
    }
    output[j] = '\0';
    return j;
}

void verify_roundtrip(const char *original, const char *decompressed) {
    if (strcmp(original, decompressed) == 0)
        printf("Data integrity verified: decompressed matches original.\n");
    else {
        printf("MISMATCH! Decompression error.\n");
        printf("  Expected: %s\n", original);
        printf("  Got     : %s\n", decompressed);
    }
}
