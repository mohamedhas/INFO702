/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newfile.hpp
 * Author: mohamed
 *
 * Created on November 18, 2016, 3:00 PM
 */


#ifndef _IMAGE2DREADER_HPP_
#define _IMAGE2DREADER_HPP_
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include <ostream>
#include <limits>
#include "Color.hpp"
#include "Image2D.hpp"
#include <iostream>

template <typename TValue>
class Image2DReader {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool read(Image & img, std::ostream & output) {
        std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

/// Specialization for gray-level images.

template <>
class Image2DReader<unsigned char> {
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;

    static void getPixel(Image *img, std::fstream& file) {
        while (file.good()) {
            char c = file.get();
            img->push(&c);
        }
    }

    void read(Image *img, std::istream & input) {
        std::string str;
        int nligneUtil = 0, nonUtil = 0;
        while (std::getline(input, str)) {
            std::istringstream istr(str);
            if ((str != "") && (str[0] == '#')) nonUtil++;
            else {
                nligneUtil++;
                switch (nligneUtil) {
                    case 1: img->getMagicNumber(str);
                        break;
                    case 2: img->getHeightnWidth(str);
                        break;
                    case 3: img->level = str;
                        break;
                    default:
                        Image2DReader<unsigned char>::getPixel(img, (std::fstream&) img->gotoLine((std::fstream&)input, nligneUtil + nonUtil));
                        return;
                        break;
                }
            }
        }
    }
};
/// Specialization for color images.

template <>
class Image2DReader<Color> {
public:
    typedef Color Value;
    typedef Image2D<Value> Image;

    static void getPixel(Image *img, std::fstream &file) {
        while(file.good()){
            Color* c = new Color(file.get(),file.get(),file.get());
            img->push(c);
        }
    }

    static void read(Image *img, std::istream &input) {
        std::string str;        
        int nligneUtil = 0, nonUtil = 0;
        while (std::getline(input, str)) {             
            std::istringstream istr(str);
            if ((str != "") && (str[0] == '#')) nonUtil++;
            else {
                nligneUtil++;
                switch (nligneUtil) {
                    case 1: img->getMagicNumber(str);
                        break;
                    case 2: img->getHeightnWidth(str);
                        break;
                    case 3: img->level = str;
                        break;
                    default:
                        Image2DReader<Color>::getPixel(img, img->gotoLine((std::fstream&)input, nligneUtil + nonUtil))
                                ;
                        return;
                        break;
                }
            }
        }
    }
};
#endif // _IMAGE2DREADER_HPP_