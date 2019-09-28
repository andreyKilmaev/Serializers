#include <iostream>
#include <fstream>
#include <string>
#include "data.pb.h"

using namespace std;

int main() {

	string str = "Hello";
	unsigned int i = 1;

	Serialize::Data d; // Создаём объект с методами для де/сериализации

	d.set_str(str); // Записываем в объект данные
	d.set_i(i);     //

	ofstream out("data.bin", std::ios_base::binary); // Создаём и открываем на запись файл data.bin
	if (d.SerializePartialToOstream(&out)) { // Если сериализация в файл удалась, то
		out.close();                         // закрываем файл

		ifstream inp("data.bin", std::ios_base::binary); // Открываем файл data.bin на чтение
		if(d.ParseFromIstream(&inp)) {                   // Если десериализация удалась, то
			str += d.str();                              //
			i += d.i();                                  //
			cout << str << " " << i << endl;             // Выводим сумму значений
		} else {                             // Если десериализация не удалась
			cout << "Faled deserialize"<< endl;
		}
	} else {                                         // Если сериализация не удалась
		out.close();
		cout << "Faled Serialize" << endl;
	}

	return 0;
}
