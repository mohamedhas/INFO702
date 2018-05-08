/*
 
 */

/* 
 * File:   WomenTimeSaerv.hpp
 * Author: mohamed
 *
 * Created on December 11, 2016, 10:37 AM
 * cette class va rendre le teint plus brillant
 */

#ifndef WOMENTIMESAVER_HPP
#define WOMENTIMESAVER_HPP

#include "Image2D.hpp"
#include "Color.hpp"

//template <typename TAccessor>

class WomenTimeSaver {
    typedef Image2D<Color> Image;
    //    typedef typename Image::template GenericIterator< TAccessor> Iterateur ;
public:

    WomenTimeSaver(Image & image) : img(image) {
    };

    int min(int *tab, int n) {
        int min = tab[0];
        for (int i = 1; i < n; i++) {
            if (min > tab[i])min = tab[i];
        }
        return min;
    }

    int max(int *tab, int n) {
        int max = tab[0];
        for (int i = 1; i < n; i++) {
            if (max < tab[i])max = tab[i];
        }
        return max;
    }

    /**
     * 
     * @param c 
     * @return si ce pixel a la couleur du teint
     */
    
    bool inRange(Color c) {
        int tab[3] = {c.red, c.green, c.blue};
        return (c.red > 95)&&(c.green > 40)&&(c.blue > 20)&&
                ((max(tab, 3) - min(tab, 3)) > 15)
                &&(abs(c.red - c.green) > 15)&&(c.red > c.green)&&(c.red > c.blue);
    }

    void paint(float per) {
        for (Image::Iterator it = img.begin(), ite = img.end(); it != ite; it++) {
            float s, v;
            int h;
            Color c = *it;
            c.getHSV(h, s, v);
            if (inRange(c)) {
                c.setHSV(h, s*per, v);
                *it = c;
            }
        }
    }


private:
    Image &img;
};

#endif /* WOMENTIMESAVER_HPP */

