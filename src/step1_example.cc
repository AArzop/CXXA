#include <boost/graph/adjacency_list.hpp>
#include <iostream>

#include "adapterGrToImg.hh"
#include "adapterImgtoGr.hh"

struct VertexProperties
{
  std::pair<int, int> coord; // 2D coordinates
  unsigned char value; // white and black image
};

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, VertexProperties> DirectedGraph;

template <class Image, class Predicate, typename T>
void fill_if(Image& img, Predicate pred, T v)
{
  static_assert(std::is_convertible<T, typename Image::value_type>::value, "");

  for (auto&& [p,value] : img.pixels())
    if (pred(p))
      value = v;
}

int main()
{
    // Graph creation
    DirectedGraph g;
    boost::add_edge (0, 1, g);
    boost::add_edge (0, 3, g);
    boost::add_edge (1, 2, g);
    boost::add_edge (2, 3, g);
    boost::add_edge (3, 1, g);
    boost::add_edge (1, 3, g);
    boost::add_edge (1, 4, g);
    boost::add_edge (4, 5, g);
    boost::add_edge (2, 8, g);

    // Set vertex's properties for 3x3
    g[0].coord = std::make_pair(0, 0);
    g[0].value = 0;
    
    g[1].coord = std::make_pair(1, 0);
    g[1].value = 0;
    
    g[2].coord = std::make_pair(2, 0);
    g[2].value = 0;
    
    g[3].coord = std::make_pair(0, 1);
    g[3].value = 56;
    
    g[4].coord = std::make_pair(1, 1);
    g[4].value = 215;
    
    g[5].coord = std::make_pair(2, 1);
    g[5].value = 127;
    
    g[6].coord = std::make_pair(0, 2);
    g[6].value = 255;
    
    g[7].coord = std::make_pair(1, 2);
    g[7].value = 255;

    g[8].coord = std::make_pair(2, 2);
    g[8].value = 42;

    //Declare Adapter with Graph g 
    AdapterGrToImg<std::pair<int, int>, unsigned char, DirectedGraph> img(g);

    std::cout << "Values of 'pixels':" << std::endl;
    for (auto&& [p, v]: img.pixels())
      std::cout << "Pixel #" << p.first << "," << p.second << ": " << (int)v << std::endl;
    std::cout << std::endl;

    fill_if(img, [](std::pair<int, int> p) { return p.first == 0; }, 55);
    
    std::cout << "Values of 'pixels':" << std::endl;
    for (auto&& [p, v]: img.pixels())
      std::cout << "Pixel #" << p.first << "," << p.second << ": " << (int)v << std::endl;
    std::cout << std::endl;

    return 0;
 }
