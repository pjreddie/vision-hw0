# CSE 455 Homework 0 #

Добро пожаловать друзья,

For the first assignment we'll just get to know the codebase a little bit and practice manipulating images, transforming things, breaking stuff, it should be fun!

Для начала мы немного познакомимся с базовыми основами написания кода и попрактикуемся работать с изображениями, будем трансоформировать их и творить с ними что хотим, вообщем будет весело.

## Image basics ##

We have a pretty basic datastructure to store images in our library. The `image` struct stores the image metadata like width, height, and number of channels. It also contains the image data stored as a floating point array. You can check it out in `src/image.h`, it looks like this:

У нас есть довольно простая структура данных для хранения изображений в нашей библиотеке. Структура `image` хранит метаданные изображения, такие как ширина, высота и количество каналов. Она также содержит данные изображения, хранящиеся в виде массива с плавающей запятой. Вы можете проверить это в `src / image.h`, это выглядит так:

    typedef struct{
        int h,w,c;
        float *data;
    } image;

We have also provided some functions for loading and saving images. Use the function:

Также предусмотрены функции загрузки и сохранения изображений. Используйте функцию:

    image im = load_image("image.jpg");

to load a new image. To save an image use:

для загрузки нового изображения. Для сохранения ихображения, используйте:

    save_image(im, "output");

which will save the image as `output.jpg`. If you want to make a new image with dimensions Width x Height x Channels you can call:

которая сохранит изображение как `output.jpg`. Если вы хотите создать новое изображение с размерами Ширина х Высота х Каналы, вызовите функцию:

    image im = make_image(w,h,c);

You should also use: 

Вы также должны использовать:

    free_image(im);
    
when you are done with an image. So it goes away. You can check out how all this is implemented in `src/load_image.c`. You probably shouldn't change anything in this file. We use the `stb_image` libary for the actual loading and saving of jpgs because that is, like, REALLY complicated. I think. I've never tried. Anywho....

когда вы закончите работать с изображением. Чтобы отчистить его. Вы можете проверить, как все это реализовано в `src/load_image.c`. Вы, наверное, не должны ничего менять в этом файле. Мы используем библиотеку `stb_image` для загрузки и сохранения jpgs, потому что это ДЕЙСТВИТЕЛЬНО очень сложно. Я думаю. Я никогда не пробовал. Во всяком случае ....

You'll be modifying the file `src/process_image.c`. We've also included a python compatability library. `uwimg.py` includes the code to access your C library from python. `tryit.py` has some example code you can run. We will build the library using `make`. Simply run the command:

Вы будете изменять файл `src/process_image.c`. Мы также включили библиотеку совместимоти python. `uwimg.py` включает в себя код для доступа к вашей библиотеке C из python. `tryit.py` содержит пример кода, который вы можете запустить. Мы создадим библиотеку, используя `make`. Просто запустите команду:

    make
    
after you make any changes to the code. Then you can quickly test your changes by running:

после внесения каких-либо изменений в код. Затем вы сможете быстро проверить свои изменения, запустив:

    ./uwimg test

You can also try running the example python code to generate some images:

Вы также можете попробовать запустить пример кода python для генерации некоторых изображений:

    python tryit.py

## 1. Getting and setting pixels ##

The most basic operation we want to do is change the pixels in an image. As we talked about in class, we represent an image as a 3 dimensional tensor. We have spatial information as well as multiple channels which combine together to form a color image:

Самая основная операция, которую мы хотим сделать, это изменить пиксели изображения. Как мы говорили на уроке, мы представляем изображение как трехмерный тензор. У нас есть пространственная информация, а также несколько каналов, которые объединяются в цветное изображение:

![RGB format](figs/rgb.png)

The convention is that the coordinate system starts at the top left of the image, like so:

По общепринятому соглашению система координат начинается в верхнем левом углу изображения, вот так:

![Image coordinate system](figs/coords.png)

In our `data` array we store the image in `CHW` format. The first pixel in data is at channel 0, row 0, column 0. The next pixel is channel 0, row 0, column 1, then channel 0, row 0, column 2, etc.

В нашем массиве `data` мы храним изображение в формате `CHW`. Первый пиксель в данных - это канал 0, строка 0, столбец 0. Следующий пиксель - это канал 0, строка 0, столбец 1, затем канал 0, строка 0, столбец 2 и т. Д.

Your first task is to fill out these two functions in `src/process_image.c`:

Ваша первая задача - заполнить эти две функции в `src/process_image.c`:

    float get_pixel(image im, int x, int y, int c);
    void set_pixel(image im, int x, int y, int c, float v);

`get_pixel` should return the pixel value at column `x`, row `y`, and channel `c`. `set_pixel` should set the pixel to the value `v`. You will need to do bounds checking to make sure the coordinates are valid for the image. `set_pixel` should simply return without doing anything if you pass in invalid coordinates. For `get_pixel` we will perform padding to the image. There are a number of possible padding strategies:

`get_pixel` должен возвращать значение пикселя в столбце `x`, строке `y` и канале `c`. `set_pixel` должен установить для пикселя значение `v`. Вам нужно будет выполнить проверку границ, чтобы убедиться, что координаты валидны для изображения. `set_pixel` должен просто возвращаться, ничего не делая, если вы передаете неверные координаты. Для `get_pixel` мы будем выполнять заполнение изображения. Существует несколько возможных стратегий заполнения:

![Image padding strategies](figs/pad.png)

We will use the `clamp` padding strategy. This means that if the programmer asks for a pixel at column -3, use column 0, or if they ask for column 300 and the image is only 256x256 you will use column 255 (because of zero-based indexing).

Мы будем использовать `clamp` стратегию заполнения. Это означает, что если программист запрашивает пиксель в столбце -3, используется столбец 0 или если он запрашивает столбец 300, а размер изображения только 256x256, используется столбец 255 (индексация начинается с 0).

We can test out our pixel-setting code on the dog image by removing all of the red channel. See line 3-8 in `tryit.py`:

Мы можем проверить наш код установки пикселей на изображении собаки, удалив весь красный канал. Смотрите строку 3-8 в `tryit.py`:

    # 1. Getting and setting pixels
    im = load_image("data/dog.jpg")
    for row in range(im.h):
        for col in range(im.w):
            set_pixel(im, row, col, 0, 0)
    save_image(im, "figs/dog_no_red")

Then try running it. Check out our very not red dog:

Затем попробуйте запустить его. Проверьте нашу очень не красную собаку:

![](figs/dog_no_red.jpg)


## 2. Copying images ##

Sometimes you have an image and you want to copy it! To do this we should make a new image of the same size and then fill in the data array in the new image. You could do this by getting and setting pixels, by looping over the whole array and just copying the floats (pop quiz: if the image is 256x256x3, how many total pixels are there?), or by using the built-in memory copying function `memcpy`.

Иногда у вас есть изображение, и вы хотите скопировать его! Для этого мы должны создать новое изображение того же размера, а затем заполнить массив данных в новом изображении. Вы можете сделать это, получая и устанавливая пиксели, зацикливая весь массив и просто копируя числа с плавающей точкой (викторина: если изображение имеет размер 256x256x3, сколько всего пикселей существует?), или используя встроенную функцию копирования памяти `memcpy`.

Fill in the function `image copy_image(image im)` in `src/process_image.c` with your code.

Заполните функцию `image copy_image (image im)` в `src / process_image.c` вашим кодом.

## 3. Grayscale image ##

Now let's start messing with some images! People like making images grayscale. It makes them look... old? Or something? Let's do it.

Теперь давайте начнем возиться с некоторыми изображениями! Людям нравится делать изображения в оттенках серого. Это заставляет их выглядеть ... старыми? Или как-либо еще? Давай сделаем это.

Remember how humans don't see all colors equally? Here's the chart to remind you:

Помните, как люди не видят все цвета одинаково? Вот диаграмма, чтобы напомнить вам:

![Eye sensitivity to different wavelengths](figs/sensitivity.png)

This actually makes a huge difference in practice. Here's a colorbar we may want to convert:

Это на самом деле имеет огромное значение на практике. Вот цветовая шкала, которую мы можем преобразовать:

![Color bar](figs/colorbar.png)

If we convert it using an equally weighted mean K = (R+G+B)/3 we get a conversion that doesn't match our perceptions of the given colors:

Если мы конвертируем её, используя одинаково взвешенное среднее K = (R + G + B) / 3, мы получаем преобразование, которое не соответствует нашему восприятию данных цветов:

![Averaging grayscale](figs/avggray.jpg)

Instead we are going to use a weighted sum. Now, there are a few ways to do this. If we wanted the most accurate conversion it would take a fair amount of work. sRGB uses [gamma compression][1] so we would first want to convert the color to linear RGB and then calculate [relative luminance](https://en.wikipedia.org/wiki/Relative_luminance).

Вместо этого мы будем использовать взвешенную сумму. Есть несколько способов сделать это. Если бы мы хотели добиться максимально точного преобразования, потребовалось бы немало усилий. sRGB использует [гамма-сжатие][1], поэтому сначала нужно преобразовать цвет в линейный RGB, а затем вычислить [относительную яркость](https://en.wikipedia.org/wiki/Relative_luminance).

But we don't care about being toooo accurate so we'll just do the quick and easy version instead. Video engineers use a calculation called [lumaв][2] to find an approximation of perceptual intensity when encoding video signal, we'll use that to convert our image to grayscale. It operates directly on the gamma compressed sRGB values that we already have! We simply perform a weighted sum:

Но мы не заботимся о том, чтобы быть слишком точными, поэтому вместо этого мы сделаем быструю и простую версию. Видеоинженеры используют вычисление, называемое [яркостью][2], чтобы найти приближение интенсивности восприятия при кодировании видеосигнала, мы будем использовать это для преобразования нашего изображения в оттенки серого. Он работает непосредственно с гамма-сжатыми значениями sRGB, которые у нас уже есть! Мы просто вычисляем взвешенную сумму:

    Y' = 0.299 R' + 0.587 G' + .114 B'

Using this conversion technique we get a pretty good grayscale image! Now we can run `tryit.py` to output `graybar.jpg`. See lines 10-13:

Используя эту технику преобразования, мы получаем довольно хорошее изображение в градациях серого! Теперь мы можем запустить `tryit.py` для вывода `graybar.jpg`. Смотрите строки 10-13:

    # 3. Grayscale image
    im = load_image("data/colorbar.png")
    graybar = rgb_to_grayscale(im)
    save_image(graybar, "graybar")

![Grayscale colorbars](figs/gray.png)

Implement this conversion for the function `rgb_to_grayscale`. Return a new image that is the same size but only one channel containing the calculated luma values.

Реализуйте это преобразование для функции `rgb_to_grayscale`. Верните новое изображение того же размера, но только один канал, содержащий рассчитанные значения яркости.

## 4. Shifting the image colors ##

Now let's write a function to add a constant factor to a channel in an image. We can use this across every channel in the image to make the image brighter or darker. We could also use it to, say, shift an image to be more or less of a given color.

Теперь давайте напишем функцию для добавления постоянного коэффициента к каналу в изображении. Мы можем использовать это для каждого канала изображения, чтобы сделать изображение ярче или темнее. Мы могли бы также использовать его, скажем, для смещения изображения, чтобы оно было более или менее определенного цвета.

Fill in the code for `void shift_image(image im, int c, float v);`. It should add `v` to every pixel in channel `c` in the image. Now we can try shifting all the channels in an image by `.4` or 40%. See lines 15-20 in `tryit.py`:

Заполните код для `void shift_image (image im, int c, float v);`. Следует добавить `v` к каждому пикселю в канале `c` на изображении. Теперь мы можем попробовать сместить все каналы в изображении на `.4` или на 40%. Смотрите строки 15-20 в `tryit.py`:

    # 4. Shift Image
    im = load_image("data/dog.jpg")
    shift_image(im, 0, .4)
    shift_image(im, 1, .4)
    shift_image(im, 2, .4)
    save_image(im, "overflow")

But wait, when we look at the resulting image `overflow.jpg` we see something bad has happened! The light areas of the image went past 1 and when we saved the image back to disk it overflowed and made weird patterns:

Но подождите, когда мы смотрим на получившееся изображение `overflow.jpg`, мы видим, что случилось что-то плохое! Светлые области изображения прошли через 1, и когда мы сохранили изображение обратно на диск, оно переполнилось и создало странные узоры:

![Overflow](figs/overflow.jpg)

## 5. Clamping the image values

Our image pixel values have to be bounded. Generally images are stored as byte arrays where each red, green, or blue value is an unsigned byte between 0 and 255. 0 represents none of that color light and 255 represents that primary color light turned up as much as possible.

Наши значения пикселей изображения должны быть ограничены. Обычно изображения хранятся в виде байтовых массивов, где каждое красное, зеленое или синее значение представляет собой байт без знака в диапазоне от 0 до 255. 0 не соответствует ни одному из этих цветных источников света, а 255 означает, что основной цветовой сигнал присутствует в максимально возможной степени.

We represent our images using floating point values between 0 and 1. However, we still have to convert between our floating point representation and the byte arrays that are stored on disk. In the example above, our pixel values got above 1 so when we converted them back to byte arrays and saved them to disk they overflowed the byte data type and went back to very small values. That's why the very bright areas of the image looped around and became dark.

Мы представляем наши изображения, используя значения с плавающей запятой в диапазоне от 0 до 1. Тем не менее, нам все еще необходимо выполнить преобразование между нашим представлением с плавающей запятой и байтовыми массивами, которые хранятся на диске. В приведенном выше примере наши значения пикселей стали больше 1, поэтому, когда мы преобразовали их обратно в байтовые массивы и сохранили их на диск, они переполнили тип данных байтов и вернулись к очень маленьким значениям. Вот почему очень яркие области изображения зацикливались и становились темными.

We want to make sure the pixel values in the image stay between 0 and 1. Implement clamping on the image so that any value below zero gets set to zero and any value above 1 gets set to one. Fill in `void clamp_image(image im);` to modify the image in-place. Then when we clamp the shifted image and save it we see much better results, see lines 22-24 in `tryit.py`:

Мы хотим, чтобы значения пикселей в изображении оставались в диапазоне от 0 до 1. Реализуем фиксирование изображения так, чтобы любое значение ниже нуля было установлено в ноль, а любое значение выше 1 - в единицу. Заполните `void fix_image (image im);`, чтобы изменить изображение. Затем, когда мы "зажимаем" смещенное изображение и сохраняем его, мы видим гораздо лучшие результаты, см. Строки 22-24 в `tryit.py`:

    # 5. Clamp Image
    clamp_image(im)
    save_image(im, "fixed")

and the resulting image, `fixed.jpg`:

и полученное изображение, `fixed.jpg`:

![](figs/fixed.jpg)

## 6. RGB to Hue, Saturation, Value ##

So far we've been focussing on RGB and grayscale images. But there are other colorspaces out there too we may want to play around with. Like [Hue, Saturation, and Value (HSV)](https://en.wikipedia.org/wiki/HSL_and_HSV). We will be translating the cubical colorspace of sRGB to the cylinder of hue, saturation, and value:

![RGB HSV conversion](figs/convert.png)

[Hue](https://en.wikipedia.org/wiki/Hue) can be thought of as the base color of a pixel. [Saturation](https://en.wikipedia.org/wiki/Colorfulness#Saturation) is the intensity of the color compared to white (the least saturated color). The [Value](https://en.wikipedia.org/wiki/Lightness) is the perception of brightness of a pixel compared to black. You can try out this [demo](http://math.hws.edu/graphicsbook/demos/c2/rgb-hsv.html) to get a better feel for the differences between these two colorspaces. For a geometric interpretation of what this transformation:

![RGB to HSV geometry](figs/rgbtohsv.png)

Now, to be sure, there are [lots of issues](http://poynton.ca/notes/colour_and_gamma/ColorFAQ.html#RTFToC36) with this colorspace. But it's still fun to play around with and relatively easy to implement. The easiest component to calculate is the Value, it's just the largest of the 3 RGB components:

    V = max(R,G,B)

Next we can calculate Saturation. This is a measure of how much color is in the pixel compared to neutral white/gray. Neutral colors have the same amount of each three color components, so to calculate saturation we see how far the color is from being even across each component. First we find the minimum value

    m = min(R,G,B)

Then we see how far apart the min and max are:

    C = V - m

and the Saturation will be the ratio between the difference and how large the max is:

    S = C / V

Except if R, G, and B are all 0. Because then V would be 0 and we don't want to divide by that, so just set the saturation 0 if that's the case.

Finally, to calculate Hue we want to calculate how far around the color hexagon our target color is.

![color hex](figs/hex.png)

We start counting at Red. Each step to a point on the hexagon counts as 1 unit distance. The distance between points is given by the relative ratios of the secondary colors. We can use the following formula from [Wikipedia](https://en.wikipedia.org/wiki/HSL_and_HSV#Hue_and_chroma):

<img src="figs/eq.svg" width="256">

There is no "correct" Hue if C = 0 because all of the channels are equal so the color is a shade of gray, right in the center of the cylinder. However, for now let's just set H = 0 if C = 0 because then your implementation will match mine.

Notice that we are going to have H = \[0,1) and it should circle around if it gets too large or goes negative. Thus we check to see if it is negative and add one if it is. This is slightly different than other methods where H is between 0 and 6 or 0 and 360. We will store the H, S, and V components in the same image, so simply replace the R channel with H, the G channel with S, etc.

## 7. HSV to RGB ##

Ok, now do it all backwards in `hsv_to_rgb`!

Finally, when your done we can mess with some images! In `tryit.py` we convert an image to HSV, increase the saturation, then convert it back, lines 26-32:

    # 6-7. Colorspace and saturation
    im = load_image("data/dog.jpg")
    rgb_to_hsv(im)
    shift_image(im, 1, .2)
    clamp_image(im)
    hsv_to_rgb(im)
    save_image(im, "dog_saturated")

![Saturated dog picture](figs/dog_saturated.jpg)

Hey that's exciting! Play around with it a little bit, see what you can make. Note that with the above method we do get some artifacts because we are trying to increase the saturation in areas that have very little color. Instead of shifting the saturation, you could scale the saturation by some value to get smoother results!

## 8. A small amount of extra credit ##

Implement `void scale_image(image im, int c, float v);` to scale a channel by a certain amount. This will give us better saturation results. Note, you will have to add the necessary lines to the header and python library, it should be very similar to what's already there for `shift_image`. Now if we scale saturation by `2` instead of just shifting it all up we get much better results:

    im = load_image("data/dog.jpg")
    rgb_to_hsv(im)
    scale_image(im, 1, 2)
    clamp_image(im)
    hsv_to_rgb(im)
    save_image(im, "dog_scale_saturated")
    
![Dog saturated smoother](figs/dog_scale_saturated.jpg)

## 9. Super duper extra credit ##

Implement RGB to [Hue, Chroma, Lightness](https://en.wikipedia.org/wiki/CIELUV#Cylindrical_representation_.28CIELCH.29), a perceptually more accurate version of Hue, Saturation, Value. Note, this will involve gamma decompression, converting to CIEXYZ, converting to CIELUV, converting to HCL, and the reverse transformations. The upside is a similar colorspace to HSV but with better perceptual properties!

## Turn it in ##

You only need to turn in one file, your `process_image.c`. Use the dropbox link on the class website.

[1]: https://en.wikipedia.org/wiki/SRGB#The_sRGB_transfer_function_("gamma")
[2]: https://en.wikipedia.org/wiki/Luma_(video)
