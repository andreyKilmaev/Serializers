#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "data.pb.h"

using namespace std;

/*
 * add: pointer, reference
 * added: float, str, map,  list
 * ������, ������� ������ protobuf: https://habr.com/ru/post/427265/
 */

int main() {

	string str("Hello");
	float f(1.1);
	map <string,list<int>> mp {{"hello", {10000,20000,40000}}, {"world", {10000,20000,40000}}};

	Serialize::Data d; // ������ ������ � �������� ��� ��/������������

	// ���������� � ������ ������
	d.set_str(str);
	d.set_f(f);
	int v(0);
	for(auto it_mp : mp) {
		d.add_mp();
		d.mutable_mp(v)->set_s(it_mp.first);
		for(auto it_i : it_mp.second) {
			d.mutable_mp(v)->add_i(it_i);
		}
		v++;
	}
//  ������ ����� �� 1 � 2??????????????
//	int *i = new int(0);
//	*i++;
//	cout << *i << endl;
//	*i++;
//	cout << *i << endl;
//	delete i;

	ofstream out("data.bin", std::ios_base::binary); // ������ � ��������� �� ������ ���� data.bin
	if (d.SerializePartialToOstream(&out)) { // ���� ������������ � ���� �������, ��
		out.close();                         // ��������� ����

		ifstream inp("data.bin", std::ios_base::binary); // ��������� ���� data.bin �� ������
		if(d.ParseFromIstream(&inp)) {                   // ���� �������������� �������, ��
			str += d.str();                              //
			f += d.f();                                  //
			cout << str << " " << f << endl;             // ������� ����� ��������
			for (auto key : d.mp()) {
				cout << key.s() << endl;
				for (auto val : key.i()) {
					cout << val << endl;
				}
			}

		} else {                             // ���� �������������� �� �������
			cout << "Faled deserialize"<< endl;
		}
	} else {                                         // ���� ������������ �� �������
		out.close();
		cout << "Faled Serialize" << endl;
	}

	return 0;
}
