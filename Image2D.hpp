/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Image2D.hpp
 * Author: mohamed
 *
 * Created on November 16, 2016, 12:52 PM
 */

#ifndef IMAGE2D_HPP
#define IMAGE2D_HPP
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include <assert.h>
#include <limits>
#include <vector>
#include <ostream>
#include <iostream>

template <typename TValue>
class Image2D {
public:
    typedef Image2D<TValue> Self; // le type de *this
    typedef TValue Value; // le type pour la valeur des pixels
    typedef std::vector<Value> Container; // le type pour stocker les valeurs des pixels de l'image.
    // Constructeur par défaut

    
    template <typename TAccessor>
    struct GenericConstIterator : public Container::const_iterator {
        typedef TAccessor Accessor;
        typedef typename Accessor::Argument ImageValue; // Color ou unsigned char
        typedef typename Accessor::Value Value; // unsigned char (pour ColorGreenAccessor)
        typedef typename Accessor::Reference Reference; // ColorGreenReference (pour ColorGreenAccessor)
  
        
        GenericConstIterator(const Image2D<ImageValue>& image, int x, int y) : Container::const_iterator(image.m_data.begin() + image.index(x, y)) {
        };
        // Accès en lecture (rvalue)

        Value operator*() const {
            return Accessor::access(Container::const_iterator::operator*());
        }

        GenericConstIterator operator++(int /* dummy_parameter */) {
            GenericConstIterator tmp = *this; // sauve la position courante.
            Container::const_iterator::operator++(); // avance avec Container::const_iterator::op++()
            return tmp; // retourne la position précédente
        }
        GenericConstIterator operator++() {
            Container::const_iterator::operator++(); // avance avec Container::const_iterator::op++()
            return *this; // retourne la position précédente
        }
    };
    
    
    template <typename TAccessor>
    struct GenericIterator : public Container::iterator {
        typedef TAccessor Accessor;
        typedef typename Accessor::Argument ImageValue; // Color ou unsigned char
        typedef typename Accessor::Value Value; // unsigned char (pour ColorGreenAccessor)
        typedef typename Accessor::Reference Reference; // ColorGreenReference (pour ColorGreenAccessor)
        GenericIterator( Image2D<ImageValue>& image, int x, int y) : Container::iterator(image.m_data.begin() + image.index(x, y)) {
        };
        // Accès en lecture (rvalue)

        Reference operator*()  {
            return Accessor::access(Container::iterator::operator*());
        }

        GenericIterator operator++(int /* dummy_parameter */) {
            GenericIterator tmp = *this; // sauve la position courante.
            Container::iterator::operator++(); // avance avec Container::const_iterator::op++()
            return tmp; // retourne la position précédente
        }
        GenericIterator operator++() {
            Container::iterator::operator++(); // avance avec Container::const_iterator::op++()
            return *this; // retourne la position précédente
        }
    };

    template <typename Accessor>
    GenericConstIterator< Accessor > start(int x = 0, int y = 0) const {
        return GenericConstIterator< Accessor >(*this, x, y);
    }

    template <typename Accessor>
    GenericConstIterator< Accessor > begin() const {
        return start<Accessor>();
    }

    template <typename Accessor>
    GenericConstIterator< Accessor > end() const {
        return start<Accessor>(0, h());
    }
    template <typename Accessor>
    GenericIterator< Accessor > start(int x = 0, int y = 0)  {
        return GenericIterator< Accessor >(*this, x, y);
    }

    template <typename Accessor>
    GenericIterator< Accessor > begin()  {
        return start<Accessor>();
    }

    template <typename Accessor>
    GenericIterator< Accessor > end()  {
        return start<Accessor>(0, h());
    }

    
    
    Image2D() {
    };
    // Constructeur avec taille w x h. Remplit tout avec la valeur g
    // (par défaut celle donnée par le constructeur par défaut).

    Image2D(int w, int h, Value g = Value()) {
        m_width = w;
        m_height = h;
        m_data.resize(w*h, g);
    }


    // Remplit l'image avec la valeur \a g.

    void fill(Value g) {
        m_data.clear();
        m_data.resize(w() * h(), g);
    }

    /// @return la largeur de l'image.

    int w() const {
        return m_width;
    }
    /// @return la hauteur de l'image.

    int h() const {
        return m_height;
    }

    /// Accesseur read-only à la valeur d'un pixel.
    /// @return la valeur du pixel(i,j)

    Value at(int i, int j) const {
        return m_data.at(m_width * j + i);
    }

    /// Accesseur read-write à la valeur d'un pixel.
    /// @return une référence à la valeur du pixel(i,j)

    Value& at(int i, int j) {
        return m_data.at(m_width * j + i);
    }

    /// Un itérateur (non-constant) simple sur l'image.

    struct Iterator : public Container::iterator {

        Iterator(Self & image, int x, int y)
        : Container::iterator(image.m_data.begin() + image.index(x, y)) {
        }
    };

    struct ConstIterator : public Container::const_iterator {

        ConstIterator(const Self & image, int x, int y)
        : Container::const_iterator(image.m_data.begin() + image.index(x, y)) {
        }
    };


    

    Iterator begin() {
        return start(0, 0);
    }
    

    Iterator end() {
        return start(0, h());
    }
    

    Iterator start(int x, int y) {
        return Iterator(*this, x, y);
    }

    

    ConstIterator begin() const {
        return start(0, 0);
    }
    

    ConstIterator end() const {
        return start(0, h());
    }
    

    ConstIterator start(int x, int y) const {
        ConstIterator const cnt = ConstIterator(*this, x, y);
        return cnt;
    }

    std::string level;
    std::string magicNumber;

    void *getData() {
        return (void*) m_data.data();
    }

    void getMagicNumber(std::string str) {
        std::istringstream istr(str);
        istr>> magicNumber;
    }

    void getHeightnWidth(std::string str) {
        std::istringstream istr(str);
        istr>>m_width;
        istr>>m_height;
    }

    std::fstream& gotoLine(std::fstream& file, unsigned int num) {
        std::cout << num << std::endl;
        file.seekg(std::ios::beg);
        for (int i = 0; i < num - 1; ++i) {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return file;
    }

    void push(void *data) {
        Value v = *((Value*) data);
        m_data.push_back(v);
    }

    int dataSize() {
        return m_data.size();
    }
    int imageSize() {
        return w()*h();
    }

private:
    Container m_data; // mes données; évitera de faire les allocations dynamiques
    int m_width; // ma largeur
    int m_height; // ma hauteur

    /// @return l'index du pixel (x,y) dans le tableau \red m_data.

    int index(int i, int j) const {
        return m_width * j + i;
    }
};
#endif /* IMAGE2D_HPP */
