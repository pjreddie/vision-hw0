#include <math.h>
#include <string.h>
#include "image.h"
#include "test.h"
#include "args.h"

int same_image(image a, image b){
    int i;
    if(a.w != b.w || a.h != b.h || a.c != b.c) return 0;
    for(i = 0; i < a.w*a.h*a.c; ++i){
//if(!within_eps(a.data[i], b.data[i])) printf("%d %f %f\n", i, a.data[i], b.data[i]);
        if(!within_eps(a.data[i], b.data[i])) return 0;
    }
    return 1;
}

void test_get_pixel(){
    image im = load_image("data/dots.png");
    // Test within image
    TEST(within_eps(0, get_pixel(im, 0,0,0)));
    TEST(within_eps(1, get_pixel(im, 1,0,1)));
    TEST(within_eps(0, get_pixel(im, 2,0,1)));

    // Test padding
    TEST(within_eps(1, get_pixel(im, 0,3,1)));
    TEST(within_eps(1, get_pixel(im, 7,8,0)));
    TEST(within_eps(0, get_pixel(im, 7,8,1)));
    TEST(within_eps(1, get_pixel(im, 7,8,2)));
}

void test_set_pixel(){
    image im = load_image("data/dots.png");
    image d = make_image(4,2,3);
    set_pixel(d, 0,0,0,0); set_pixel(d, 0,0,1,0); set_pixel(d, 0,0,2,0); 
    set_pixel(d, 1,0,0,1); set_pixel(d, 1,0,1,1); set_pixel(d, 1,0,2,1); 
    set_pixel(d, 2,0,0,1); set_pixel(d, 2,0,1,0); set_pixel(d, 2,0,2,0); 
    set_pixel(d, 3,0,0,1); set_pixel(d, 3,0,1,1); set_pixel(d, 3,0,2,0); 

    set_pixel(d, 0,1,0,0); set_pixel(d, 0,1,1,1); set_pixel(d, 0,1,2,0); 
    set_pixel(d, 1,1,0,0); set_pixel(d, 1,1,1,1); set_pixel(d, 1,1,2,1); 
    set_pixel(d, 2,1,0,0); set_pixel(d, 2,1,1,0); set_pixel(d, 2,1,2,1); 
    set_pixel(d, 3,1,0,1); set_pixel(d, 3,1,1,0); set_pixel(d, 3,1,2,1); 

    // Test images are same
    TEST(same_image(im, d));
}

void test_grayscale()
{
    image im = load_image("data/colorbar.png");
    image gray = rgb_to_grayscale(im);
    image g = load_image("figs/gray.png");
    TEST(same_image(gray, g));
}

void test_copy()
{
    image im = load_image("data/dog.jpg");
    image c = copy_image(im);
    TEST(same_image(im, c));
}

void test_shift()
{
    image im = load_image("data/dog.jpg");
    image c = copy_image(im);
    shift_image(c, 1, .1);
    TEST(within_eps(im.data[0], c.data[0]));
    TEST(within_eps(im.data[im.w*im.h+13] + .1,  c.data[im.w*im.h + 13]));
    TEST(within_eps(im.data[2*im.w*im.h+72],  c.data[2*im.w*im.h + 72]));
    TEST(within_eps(im.data[im.w*im.h+47] + .1,  c.data[im.w*im.h + 47]));
}

void test_rgb_to_hsv()
{
    image im = load_image("data/dog.jpg");
    rgb_to_hsv(im);
    image hsv = load_image("figs/dog.hsv.png");
    TEST(same_image(im, hsv));
}

void test_hsv_to_rgb()
{
    image im = load_image("data/dog.jpg");
    image c = copy_image(im);
    rgb_to_hsv(im);
    hsv_to_rgb(im);
    TEST(same_image(im, c));
}

int do_test()
{
    TEST('1' == '1');
    TEST('0' == '1');
    return 0;
}

void run_tests()
{
    test_get_pixel();
    test_set_pixel();
    test_copy();
    test_shift();
    test_grayscale();
    test_rgb_to_hsv();
    test_hsv_to_rgb();
    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}

int main(int argc, char **argv)
{
    char *in = find_char_arg(argc, argv, "-i", "data/dog.jpg");
    char *out = find_char_arg(argc, argv, "-o", "out");
    //float scale = find_float_arg(argc, argv, "-s", 1);
    if(argc < 2){
        printf("usage: %s [test | grayscale]\n", argv[0]);  
    } else if (0 == strcmp(argv[1], "test")){
        run_tests();
    } else if (0 == strcmp(argv[1], "grayscale")){
        image im = load_image(in);
        image g = rgb_to_grayscale(im);
        save_image(g, out);
        free_image(im);
        free_image(g);
    }
    return 0;
}
