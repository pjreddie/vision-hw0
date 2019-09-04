#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
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
    // Overflows Taken care of ::
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x > im.w) x = im.w -1;
    if(y > im.h) y = im.h -1 ;

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

    free_image(im);
    return value; 
    // free_image(im);
}

// WORKS FINE BUT HAVE TO IMPLEMENT OVERFLOW
void set_pixel(image im, int x, int y, int c, float v)
{
    // Overflows taken care of
    if (x < 0)
        return;
    if (y < 0)
        return;
    if (x > im.w)
        return;
    if (y > im.h)
        return;
        
    // TODO Fill this in
    image * im_ptr;
    im_ptr = &im;
    float * data = im_ptr->data;

    float(*data_matrix) [im.w][im.h] = data;
    float * value = (*(*(data_matrix +c) + x) + y);
    *value = v; 

    // free_image(im);

}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    //memcpy (dest_struct, source_struct, sizeof (*dest_struct));
    // image * copy_ptr = &copy;
    memcpy(&copy, &im, sizeof(copy));          // Not Sure if this will work

    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);        // Creates a image struct with *data contnaning 
                                                   // 1 Channel

    // Creating pointers to struct
    // First  pointer to gray image
    image * ptr_gray , * ptr_im;
    // Point to the address of the struct objects
    // Gray Image
    ptr_gray = &gray; 
    float * gray_data = ptr_gray->data;
    float(*gray_data_matrix) [im.w][im.h] = gray_data;
    // memset(gray_data_matrix, 0, sizeof gray_data_matrix); 
    // Given Image
    ptr_im = &im; 
    float * im_data = ptr_im->data;
    float(*im_data_matrix) [im.w][im.h] = im_data;


    // Define the data members of gray to be that of im:
    ptr_gray->h = ptr_im->h;
    // ptr_gray->c = ptr_im->c;
    ptr_gray->w = ptr_im->w;

    // Now we have the weighted mean like:
    //Y' = 0.299 R' + 0.587 G' + .114 B'

    // So for a given *data I have to caculate the value over the whole 3-D Matrix
    float value;
    for(int channels=0; channels < im.c ; channels++){
        if(channels == 0) {value = 0.299;}
        else if(channels == 1) {value = 0.587;}
        else if(channels == 2) {value = 0.114;}
        for(int width = 0; width < gray.w ; width++){
            for(int height = 0; height < gray.h; height++){
                (*gray_data_matrix)[width][height] +=  
                (*(*(*(im_data_matrix +channels) + width) + height))*value;
            }
        
        }
    }

    // free_image(im);
    // free_image(gray);

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
