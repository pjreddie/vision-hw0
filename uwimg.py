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
lib = CDLL("libuwimg.so", RTLD_GLOBAL)

make_image = lib.make_image
make_image.argtypes = [c_int, c_int, c_int]
make_image.restype = IMAGE

free_image = lib.free_image
free_image.argtypes = [IMAGE]

get_channel = lib.get_channel
get_channel.argtypes = [IMAGE, c_int]
get_channel.restype = IMAGE

pad_image = lib.pad_image
pad_image.argtypes = [IMAGE, c_int]
pad_image.restype = IMAGE

grayscale_to_rgb = lib.grayscale_to_rgb
grayscale_to_rgb.argtypes = [IMAGE, c_float, c_float, c_float]
grayscale_to_rgb.restype = IMAGE

rgb_to_grayscale = lib.rgb_to_grayscale
rgb_to_grayscale.argtypes = [IMAGE]
rgb_to_grayscale.restype = IMAGE

load_image = lib.load_image
load_image.argtypes = [c_char_p]
load_image.restype = IMAGE

save_image = lib.save_image
save_image.argtypes = [IMAGE, c_char_p]

if __name__ == "__main__":
    im = load_image("data/dog.jpg")
    save_image(im, "hey")

    

