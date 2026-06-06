/*
 * rle_compress.c
 * Run-Length Encoding (RLE) — Compression
 *
 * Author : Meenakshi Mamidala
 * GitHub : github.com/meenakshi-mamidala
 *
 * Complexity:
 *   Time  : O(n)  — single pass through the input string
 *   Space : O(n)  — output buffer proportional to input size
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rle.h"

int compress(const char *input, char *output) {
    int i = 0, j = 0;
    int n = strlen(input);
    if (n == 0) { output[0] = '\0'; return 0; }

    while (i < n) {
        char current = input[i];
        int count = 1;
        while (i + count < n && input[i + count] == current) count++;
        if (count > 1) j += sprintf(output + j, "%d", count);
        output[j++] = current;
        i += count;
    }
    output[j] = '\0';
    return j;
}

void analyze_compression(const char *original, const char *compressed) {
    int orig_len = strlen(original);
    int comp_len = strlen(compressed);
    float ratio  = (orig_len > 0) ? (1.0f - (float)comp_len / orig_len) * 100 : 0;

    printf("\n--- Compression Analysis ---\n");
    printf("Original  : %s\n", original);
    printf("Compressed: %s\n", compressed);
    printf("Original size  : %d characters\n", orig_len);
    printf("Compressed size: %d characters\n", comp_len);
    if      (comp_len < orig_len) printf("Space saved    : %.1f%%\n", ratio);
    else if (comp_len == orig_len) printf("Result: No size change.\n");
    else    printf("Result: RLE overhead (data not repetitive enough).\n");
    printf("----------------------------\n\n");
}
