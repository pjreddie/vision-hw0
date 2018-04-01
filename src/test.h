#include <stdio.h>
#define EPS .005
int tests_total = 0;
int tests_fail = 0;
#define TEST(EX) do { ++tests_total; if(!(EX)) {\
    fprintf(stderr, "failed: [%s] testing [%s] in %s, line %d\n", __FUNCTION__, #EX, __FILE__, __LINE__); \
    ++tests_fail; }} while (0)

int within_eps(float a, float b){
    return a-EPS<b && b<a+EPS;
}
