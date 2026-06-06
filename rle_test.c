/*
 * rle_test.c
 * Run-Length Encoding (RLE) — Test Suite
 *
 * Author : Meenakshi Mamidala
 * GitHub : github.com/meenakshi-mamidala
 *
 * Description:
 *   Automated test cases to validate both compression and
 *   decompression logic. Verifies data integrity (roundtrip).
 *
 * How to compile & run:
 *   gcc rle_compress.c rle_decompress.c rle_test.c -o rle_test
 *   ./rle_test
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 10000

// ── Forward declarations ──────────────────────────────────────────
int compress(const char *input, char *output);
int decompress(const char *input, char *output);

// ── Test runner ───────────────────────────────────────────────────
int tests_passed = 0;
int tests_failed = 0;

void run_test(const char *label, const char *input,
              const char *expected_compressed) {
    char compressed[MAX_SIZE * 2];
    char decompressed[MAX_SIZE * 10];

    compress(input, compressed);
    decompress(compressed, decompressed);

    int compress_ok  = (strcmp(compressed,   expected_compressed) == 0);
    int roundtrip_ok = (strcmp(decompressed, input)               == 0);

    printf("Test: %-35s ", label);
    if (compress_ok && roundtrip_ok) {
        printf("PASS\n");
        tests_passed++;
    } else {
        printf("FAIL\n");
        if (!compress_ok) {
            printf("  Expected compressed : %s\n", expected_compressed);
            printf("  Got compressed      : %s\n", compressed);
        }
        if (!roundtrip_ok) {
            printf("  Roundtrip mismatch!\n");
            printf("  Original     : %s\n", input);
            printf("  Decompressed : %s\n", decompressed);
        }
        tests_failed++;
    }
}

// ── Complexity report ─────────────────────────────────────────────
void complexity_report(const char *input) {
    char compressed[MAX_SIZE * 2];
    compress(input, compressed);

    int orig = strlen(input);
    int comp = strlen(compressed);
    float saved = (orig > 0) ? (1.0f - (float)comp / orig) * 100.0f : 0;

    printf("  Input (%3d chars): %-30s → Compressed (%3d chars): %-20s  [%.1f%% %s]\n",
           orig, input, comp, compressed,
           (saved >= 0) ? saved : -saved,
           (saved > 0) ? "saved" : (saved == 0 ? "no change" : "overhead"));
}

// ── Main ──────────────────────────────────────────────────────────
int main() {
    printf("========================================\n");
    printf("   RLE Compression — Test Suite\n");
    printf("   Author: Meenakshi Mamidala\n");
    printf("========================================\n\n");

    // ── Functional tests ─────────────────────────────────────────
    printf("[ Functional Tests ]\n");
    run_test("Basic repeated chars",       "AAAABBBCC",       "4A3B2C");
    run_test("Single chars (no compress)", "ABCD",            "ABCD");
    run_test("All same character",         "AAAAAAAAAA",      "10A");
    run_test("Mixed single & repeated",    "AABBC",           "2A2BC");
    run_test("Lowercase letters",          "aaabbbccc",       "3a3b3c");
    run_test("Digits as data (letters only)", "AAABBBCCC",       "3A3B3C");
    run_test("Single character string",    "Z",               "Z");
    run_test("Long repetition",            "BBBBBBBBBBBBBBB", "15B");
    run_test("Alternating (worst case)",   "ABABAB",          "ABABAB");
    run_test("Spaces in input",            "AAA   BB",        "3A3 2B");

    printf("\n");

    // ── Space complexity / performance report ────────────────────
    printf("[ Space Complexity Report — Various Datasets ]\n");
    complexity_report("AAAABBBCC");
    complexity_report("ABCDEFGHIJ");
    complexity_report("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    complexity_report("ABABABABABABABABABABABABABABABABABABABABABABABABABABAB");
    complexity_report("MMMMMMMMMMMEENAKSHI");
    complexity_report("   TELANGANA   ");
    printf("\n");

    // ── Summary ──────────────────────────────────────────────────
    printf("========================================\n");
    printf("Results: %d passed, %d failed\n", tests_passed, tests_failed);
    if (tests_failed == 0)
        printf("All tests passed! Data integrity verified.\n");
    else
        printf("Some tests failed. Check logic above.\n");
    printf("========================================\n");

    return (tests_failed == 0) ? 0 : 1;
}
