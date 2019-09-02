#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"


/* All the help Needed*/
// Since the image is a struct that is defined like this
// typedef struct{
//     int w,h,c;           // w defines width // h defines height // c defines channels 
//     float *data;   // data points to an array that contains all the data pixels in CHW format
// }image;



// WORKS FINE
float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    // im struct contains *data which contains pixel values in the form of CHW(CHannel,Row, Colums)
    // im has 4 data members that are h,w,c and *data
    // int height = im_ptr->h;
    // int width = im_ptr->w;
    // int channels = im_ptr->c;
    image * im_ptr;
    im_ptr = &im;
    float *data = im_ptr->data;
    // float value = *(*(*(data+c)+x)+y));
    // return value;

    float(*data_matrix) [im.w][im.h] = data;
    float value = *(*(*(data_matrix +c) + x) + y);
    return value; 
}

// WORKS FINE BUT HAVE TO IMPLEMENT OVERFLOW
void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    image * im_ptr;
    im_ptr = &im;
    float * data = im_ptr->data;

    float(*data_matrix) [im.w][im.h] = data;
    float * value = (*(*(data_matrix +c) + x) + y);
    *value = v; 

}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
}

void clamp_image(image im)
{
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
