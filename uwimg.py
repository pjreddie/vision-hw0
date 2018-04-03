import sys, os
from ctypes import *
import math
import random

def c_array(ctype, values):
    arr = (ctype*len(values))()
    arr[:] = values
    return arr

class IMAGE(Structure):
    _fields_ = [("w", c_int),
                ("h", c_int),
                ("c", c_int),
                ("data", POINTER(c_float))]


#lib = CDLL("/home/pjreddie/documents/455/libuwimg.so", RTLD_GLOBAL)
#lib = CDLL("libuwimg.so", RTLD_GLOBAL)
lib = CDLL(os.path.join(os.path.dirname(__file__), "libuwimg.so"), RTLD_GLOBAL)

make_image = lib.make_image
make_image.argtypes = [c_int, c_int, c_int]
make_image.restype = IMAGE

free_image = lib.free_image
free_image.argtypes = [IMAGE]

get_pixel = lib.get_pixel
get_pixel.argtypes = [IMAGE, c_int, c_int, c_int]
get_pixel.restype = c_float

set_pixel = lib.set_pixel
set_pixel.argtypes = [IMAGE, c_int, c_int, c_int, c_float]

rgb_to_grayscale = lib.rgb_to_grayscale
rgb_to_grayscale.argtypes = [IMAGE]
rgb_to_grayscale.restype = IMAGE

rgb_to_hsv = lib.rgb_to_hsv
rgb_to_hsv.argtypes = [IMAGE]

hsv_to_rgb = lib.hsv_to_rgb
hsv_to_rgb.argtypes = [IMAGE]

shift_image = lib.shift_image
shift_image.argtypes = [IMAGE, c_int, c_float]

clamp_image = lib.clamp_image
clamp_image.argtypes = [IMAGE]

load_image_lib = lib.load_image
load_image_lib.argtypes = [c_char_p]
load_image_lib.restype = IMAGE

def load_image(f):
    return load_image_lib(f.encode('ascii'))

save_image_lib = lib.save_image
save_image_lib.argtypes = [IMAGE, c_char_p]

def save_image(im, f):
    return save_image_lib(im, f.encode('ascii'))

if __name__ == "__main__":
    im = load_image("data/dog.jpg")
    save_image(im, "hey")

    

