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
  if ( argc < 4   ) 
    { 
      std::cerr << "Usage: save-green-channel <input.ppm> <output.pgm> <pourcentage de saturation>" << std::endl;
      return 0;
    }
  else{
  ColorImage2D img;
  std::ifstream input( argv[1] ); // récupère le 1er argument.
    ColorImage2DReader::read( &img, input );

    
  input.close();
  WomenTimeSaver w(img);
  w.paint(atof(argv[3]));

  
  std::ofstream output( argv[2] ); // récupère le 2eme argument.
  Image2DWriter<Color>::write(img,output,false);
  output.close();
  return 0;
  }
}