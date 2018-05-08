#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"
#include "WomenTimeSaver.hpp"
int main( int argc, char** argv )
{
  typedef Image2D<Color> ColorImage2D;
  typedef Image2DReader<Color> ColorImage2DReader;
  typedef ColorImage2D::Iterator ColorIterator;
  if ( argc < 3 ) 
    { 
      std::cerr << "Usage: save-green-channel <input.ppm> <output.pgm>" << std::endl;
      return 0;
    }
  ColorImage2D img;
  std::ifstream input( argv[1] ); // récupère le 1er argument.
    ColorImage2DReader::read( &img, input );

    
  input.close();
  Histogramme<Color,ColorVAccessor>h(img) ;
  h.egaliser();

  
  std::ofstream output( argv[2] ); // récupère le 2eme argument.
  Image2DWriter<Color>::write(img,output,false);
  output.close();
  return 0;
}