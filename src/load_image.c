// You probably don't want to edit this file
#include <stdio.h>
#include <stdlib.h>

#include "image.h"

image make_empty_image(int w, int h, int c)
{
    image out;
    out.data = 0;
    out.h = h;
    out.w = w;
    out.c = c;
    return out;
}

image make_image(int w, int h, int c)
{
    image out = make_empty_image(w,h,c);
    out.data = calloc(h*w*c, sizeof(float));
    return out;
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void save_image_stb(image im, const char *name)
{
    char buff[256];
    sprintf(buff, "%s.jpg", name);
    unsigned char *data = calloc(im.w*im.h*im.c, sizeof(char));
    int i,k;
    for(k = 0; k < im.c; ++k){
        for(i = 0; i < im.w*im.h; ++i){
            data[i*im.c+k] = (unsigned char) roundf((255*im.data[i + k*im.w*im.h]));
        }
    }
    //int success = stbi_write_png(buff, im.w, im.h, im.c, data, im.w*im.c);
    int success = stbi_write_jpg(buff, im.w, im.h, im.c, data, 100);
    free(data);
    if(!success) fprintf(stderr, "Failed to write image %s\n", buff);
}

void save_image(image im, const char *name)
{
    save_image_stb(im, name);
}

// 
// Load an image using stb
// channels = [0..4]
// channels > 0 forces the image to have that many channels
//
image load_image_stb(char *filename, int channels)
{
    int w, h, c;
    unsigned char *data = stbi_load(filename, &w, &h, &c, channels);
    if (!data) {
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n",
            filename, stbi_failure_reason());
        exit(0);
    }
    if (channels) c = channels;
    int i,j,k;
    image im = make_image(w, h, c);
    for(k = 0; k < c; ++k){
        for(j = 0; j < h; ++j){
            for(i = 0; i < w; ++i){
                int dst_index = i + w*j + w*h*k;
                int src_index = k + c*i + c*w*j;
                im.data[dst_index] = (float)data[src_index]/255.;
            }
        }
    }
    //We don't like alpha channels, #YOLO
    if(im.c == 4) im.c = 3;
    free(data);
    return im;
}

image load_image(char *filename)
{
    image out = load_image_stb(filename, 0);
    return out;
}

void free_image(image im)
{
    free(im.data);
}
