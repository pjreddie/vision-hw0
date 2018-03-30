#include <stdio.h>
int tests_total = 0;
int tests_fail = 0;
#define TEST(EX) do { ++tests_total; if(!(EX)) {\
    fprintf(stderr, "test failed: (%s) in %s, line %d\n", #EX, __FILE__, __LINE__); \
    ++tests_fail; return 0;}} while (0)
