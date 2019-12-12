#include <iostream>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

using namespace std;

int main() {

	map<string, list<complex<float>>> mp= { {"real", { {1.0f, 0},
															 {2.2f, 0},
															 {3.3f, 0} }},
												  {"imaginary", { {0, -1.0f},
												 				  {0, -2.9932f},
													 			  {0, -3.5f} }} }
								   , mp2;
	vector<string> str = {"Hello", "world"}, str2;

    constexpr std::size_t flags =
         yas::mem // IO type
        |yas::json; // IO format

    auto buf = yas::save<flags>(
        YAS_OBJECT("myobject", mp, str)
    );

    yas::load<flags>(buf,
        YAS_OBJECT_NVP("myobject"
            ,("mp", mp2)
            ,("str", str2)
        )
    );
    if (mp == mp2 && str == str2) {
    	cout << "All is right" << endl;
    } else {
    	cout << "All is bad" << endl;
    }
	return 0;
}
