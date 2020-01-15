#include <iostream>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>

using namespace std;

class Stuff
{
  public:
    Stuff() = default;

    void fillData()
    {
    	data_map = { {"real", { {1.0f, 0},
                          {2.2f, 0},
                          {3.3f, 0} }},
               {"imaginary", { {0, -1.0f},
                               {0, -2.9932f},
                               {0, -3.5f} }} };
    	data_str = {"Hello", "world"};
    }

  private:
    map<string, list<complex<float>>> data_map;
    vector<string> data_str;


    friend class cereal::access;

    template <class Archive>
    void serialize( Archive & ar )
    {
      ar( CEREAL_NVP(data_map), CEREAL_NVP(data_str) );
    }
};

int main()
{
  cereal::BinaryOutputArchive output(std::cout); // stream to cout

  Stuff myStuff;
  myStuff.fillData();

  output( cereal::make_nvp("best data ever", myStuff) );
  
  return 0;
}




