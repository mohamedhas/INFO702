#ifndef _COLOR_HPP_
#define _COLOR_HPP_
#include <iostream>

/**
   Représente une couleur avec un codage RGB. Ce codage utilise 3
   octets, le premier octet code l'intensité du rouge, le deuxième
   l'intensité du vert, le troisième l'intensité du bleu.
 */


struct Color {
    typedef unsigned char Byte;
    /// Code les 3 canaux RGB sur 3 octets.
    Byte red, green, blue;
    //  float s,v ; int h ; 

    Color() {
    }
    /// Crée la couleur spécifiée par (_red,_green,_blue).

    Color(Byte _red, Byte _green, Byte _blue)
    : red(_red), green(_green), blue(_blue) {
    }
    /// @return l'intensité de rouge (entre 0.0 et 1.0)

    float r() const {
        return ( (float) red) / 255.0;
    }
    /// @return l'intensité de vert (entre 0.0 et 1.0)

    float g() const {
        return ( (float) green) / 255.0;
    }
    /// @return l'intensité de bleu (entre 0.0 et 1.0)

    float b() const {
        return ( (float) blue) / 255.0;
    }
    /// Sert à désigner un canal.

    enum Channel {
        Red, Green, Blue
    };
    /// @return le canal le plus intense.

    Channel argmax() const {
        if (red >= green) return red >= blue ? Red : Blue;
        else return green >= blue ? Green : Blue;
    }
    /// @return l'intensité maximale des canaux

    float max() const {
        return std::max(std::max(r(), g()), b());
    }
    /// @return l'intensité minimale des canaux

    float min() const {
        return std::min(std::min(r(), g()), b());
    }

    /**
       Convertit la couleur RGB en le modèle HSV (TSV en français).
       @param h la teinte de la couleur (entre 0 et 359), hue en anglais.
       @param s la saturation de la couleur (entre 0.0 et 1.0)
       @param v la valeur ou brillance de la couleur (entre 0.0 et 1.0).
     */
    void getHSV(int & h, float & s, float & v) const {
        // Taking care of hue
        if (max() == min()) h = 0;
        else {
            switch (argmax()) {
                case Red: h = ((int) (60.0 * (g() - b()) / (max() - min()) + 360.0)) % 360;
                    break;
                case Green: h = ((int) (60.0 * (b() - r()) / (max() - min()) + 120.0));
                    break;
                case Blue: h = ((int) (60.0 * (r() - g()) / (max() - min()) + 240.0));
                    break;
            }
        }
        // Taking care of saturation
        s = max() == 0.0 ? 0.0 : 1.0 - min() / max();
        // Taking care of value
        v = max();
    }
    

    void setHSV(int h, float s, float v) {
        float ha =  h/60.0 ; 
        float c = v*s;
        float x =  c* (1.0 - fabs( (fmod(ha,2.0)) - 1.0) ) ;
        float r,g,b; 
        if(ha>=0.0&&ha<=1.0){
            r=c ;g=x ;b=0.0 ;
        }else if(ha>=1.0&&ha<=2.0){
            r=x ;g=c ;b=0.0 ;
        }
        else if(ha>=2.0&&ha<=3.0){
            r=0.0 ;g=c ;b=x ;
        }
        else if(ha>=3.0&&ha<=4.0){
            r=0.0 ;g=x ;b=c ;
        }
        else if(ha>=4.0&&ha<=5.0){
            r=x ;g=0.0 ;b=c ;
        }
        else if(ha>=5.0&&ha<6.0){
            r=c ;g=0.0 ;b=x ;
        }
        float m = v-c ;        
        red=floor(((r+m)*255.0)+0.5);green=floor(((g+m)*255.0)+0.5);blue=floor(((b+m)*255.0)+0.5);
    }
};

std::ostream &operator<<(std::ostream& out, Color c) {
    out << (int) c.red << "    " << (int) c.green << "   " << (int) c.blue;
    return out;
}
#endif //_COLOR_HPP_
