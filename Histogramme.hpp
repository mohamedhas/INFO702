/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Histogramme.hpp
 * Author: mohamed
 *
 * Created on November 9, 2016, 11:06 PM
 */

#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include "Image2D.hpp"
#define Taille 256

template <typename TColor, typename TAccessor>
class Histogramme {
    typedef Image2D<TColor> Image;
    typedef typename Image::template GenericIterator< TAccessor> Iterateur;
    typedef unsigned char Byte;
public:
    float *get_hi_tab();
    float *get_Hi_tab();

    void calculer_somme() {
        for (Iterateur it = image.template begin<TAccessor>(), ite = image.template end<TAccessor>(); it != ite; it++)
            somme_tab[(*it)] = somme_tab[(*it)] + 1;
    }

    void calculer_hi() {
        calculer_somme();
        for (int i = 0; i < Taille; i++) hi_tab[i] = somme_tab[i] / image.imageSize();
    }

    void calaculer_Hi() {
        calculer_somme();
        for (int i = 0; i < Taille; i++) {

            if (i) somme_tab[i] += somme_tab[i - 1];
            Hi_tab[i] = (float) somme_tab[i] / image.imageSize();

        }
    }

    void init() {
        for (int i = 0; i < Taille; i++) {
            somme_tab[i] = 0;
        }
    }


    Byte egalisation(int j) {

        return (Byte) (255 * Hi_tab[j]);
    }

    void egaliser() {
        calaculer_Hi();
        for (Iterateur it = image.template begin<TAccessor>(), ite = image.template end<TAccessor>(); it != ite; it++) {
            Byte b = egalisation(*it);
            *it = b;
        }

    }

    Histogramme(Image2D<TColor>& img) : image(img) {
        init();
    };

private:
    float hi_tab[Taille];
    float Hi_tab[Taille];
    int somme_tab[Taille];
    Image& image;
};

#endif /* HISTOGRAMME_HPP */

