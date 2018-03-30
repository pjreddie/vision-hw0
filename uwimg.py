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

load_image = lib.load_image
load_image.argtypes = [c_char_p, c_int, c_int]
load_image.restype = IMAGE

save_image = lib.save_image
save_image.argtypes = [IMAGE, c_char_p]

if __name__ == "__main__":
    im = load_image("data/dog.jpg", 0, 0)
    save_image(im, "hey")

    

