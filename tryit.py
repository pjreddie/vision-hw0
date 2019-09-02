from uwimg import *
import os
import shutil

def tryit_made_figures():
    os.mkdir(os.path.join(os.getcwd(), "Tryit_Photos"))


# 1. Getting and setting pixels
def get_set_pixels():
    im = load_image("data/dog.jpg")
    for row in range(im.h):
        for col in range(im.w):
            # set_pixel takes in these params (*image, column, row, channel, value_to_set)
            # set_pixel(im, col, row, 0, 0)     # No red      
            # set_pixel(im, col, row, 1, 0)      # No green
            set_pixel(im, col, row, 2, 0)      # No blue
            # print(im[row][col][0])
    save_image(im, "Tryit_Photos/dog_no_red")

# 3. Grayscale image
def grayscaleImage():
    im = load_image("data/colorbar.png")
    graybar = rgb_to_grayscale(im)
    save_image(graybar, "Tryit_Photos/graybar")

# 4. Shift Image
def shiftImage():
    im = load_image("data/dog.jpg")
    shift_image(im, 0, .4)
    shift_image(im, 1, .4)
    shift_image(im, 2, .4)
    save_image(im, "Tryit_Photos/overflow")

# 5. Clamp Image
def clampImage():
    im = load_image("data/dog.jpg")
    clamp_image(im)
    save_image(im, "Tryit_Photos/doglight_fixed")

# 6-7. Colorspace and saturation
def colorspace_and_saturation():
    im = load_image("data/dog.jpg")
    rgb_to_hsv(im)
    shift_image(im, 1, .2)
    clamp_image(im)
    hsv_to_rgb(im)
    save_image(im, "Tryit_Photos/dog_saturated")

if __name__ == "__main__":
    if os.path.isdir(os.path.join(os.getcwd(), "Tryit_Photos")):
        shutil.rmtree(os.path.join(os.getcwd(), "Tryit_Photos"))
        tryit_made_figures()
    else:
        tryit_made_figures()
    
    #Utlity Functions been called
    get_set_pixels()
    # grayscaleImage()
    # shiftImage()
    # clampImage()
    # colorspace_and_saturation()



