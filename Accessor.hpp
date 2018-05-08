/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Accessor.hpp
 * Author: mohamed
 *
 * Created on November 25, 2016, 2:40 PM
 */

#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include "Color.hpp"
/// Accesseur trivial générique

template <typename TValue>
struct TrivialAccessor {
    typedef TValue Value;
    typedef Value Argument;
    typedef Value& Reference;
    // Acces en lecture.

    static Value access(const Argument & arg) {
        return arg;
    }
    // Acces en écriture.

    static Reference access(Argument & arg) {
        return arg;
    }
};

// Accesseur trivial pour une image en niveaux de gris
typedef TrivialAccessor<unsigned char> GrayLevelTrivialAccessor;
// Accesseur trivial pour une image en couleur.
typedef TrivialAccessor<Color> ColorTrivialAccessor;
/// Accesseur à la composante verte.

struct ColorGreenAccessor {
    typedef unsigned char Value;
    typedef Color Argument;
    /// Même astuce que pour les références à un bit dans un tableau de bool.

    struct ColorGreenReference {
        Argument & arg;

        ColorGreenReference(Argument & someArg) : arg(someArg) {
        }
        // Accesseur lvalue (écriture)
        // permet d'écrire *it = 120 pour changer l'intensité du vert

        ColorGreenReference& operator=(Value val) {
            arg.green = val;
            return *this;
        }
        // Accesseur rvalue (lecture)
        // permet d'écrire *it pour récupérer l'intensité du vert

        operator Value() const {
            return arg.green; // arg.green est de type Value.
        }
    };
    typedef ColorGreenReference Reference;
    // Acces en lecture.

    static Value access(const Argument & arg) {
        return arg.green;
    }
    // Acces en écriture.

    static Reference access(Argument & arg) {
        return ColorGreenReference(arg);
    }
};
struct ColorBlueAccessor {
    typedef unsigned char Value;
    typedef Color Argument;


    struct ColorBlueReference {
        Argument & arg;

        ColorBlueReference(Argument & someArg) : arg(someArg) {
        }

        ColorBlueReference& operator=(Value val) {
            arg.blue = val;
            return *this;
        }


        operator Value() const {
            return arg.blue; 
        }
    };
    typedef ColorBlueReference Reference;
    // Acces en lecture.

    static Value access(const Argument & arg) {
        return arg.blue;
    }
    // Acces en écriture.

    static Reference access(Argument & arg) {
        return ColorBlueReference(arg);
    }
};

struct ColorRedAccessor {
    typedef unsigned char Value;
    typedef Color Argument;


    struct ColorRedReference {
        Argument & arg;

        ColorRedReference(Argument & someArg) : arg(someArg) {
        }

        ColorRedReference& operator=(Value val) {
            arg.red = val;
            return *this;
        }
        

        operator Value() const {
            return arg.red; 
        }
    };
    typedef ColorRedReference Reference;
    // Acces en lecture.

    static Value access(const Argument & arg) {
        return arg.red;
    }
    // Acces en écriture.

    static Reference access(Argument & arg) {
        return ColorRedReference(arg);
    }
};
struct ColorVAccessor {
    typedef unsigned char Value;
    typedef Color Argument;

    struct ColorVReference {
        Argument & arg;

        ColorVReference(Argument & someArg) : arg(someArg) {
        }


        ColorVReference& operator=(Value val) {
            float s,v;int h ; 
            arg.getHSV(h,s,v);
            v = ((float)val)/255;
            arg.setHSV(h,s,v);
            return *this;
        }

        operator Value() const {
            float s,v;int h ; 
            arg.getHSV(h,s,v);
            return v*255; 
        }
    };
    typedef ColorVReference Reference;
    // Acces en lecture.

    static Value access(const Argument & arg) {
        float s,v;int h ; 
        arg.getHSV(h,s,v);
        return v*255;
    }
    // Acces en écriture

    static Reference access(Argument & arg) {
        return ColorVReference(arg);
    }
};

#endif /* ACCESSOR_HPP */

