#include <iostream>
#include <fstream>
#include <string>
#include "data.pb.h"

using namespace std;

int main() {

	string str = "Hello";
	unsigned int i = 1;

	Serialize::Data d; // ������ ������ � �������� ��� ��/������������

	d.set_str(str); // ���������� � ������ ������
	d.set_i(i);     //

	ofstream out("data.bin", std::ios_base::binary); // ������ � ��������� �� ������ ���� data.bin
	if (d.SerializePartialToOstream(&out)) { // ���� ������������ � ���� �������, ��
		out.close();                         // ��������� ����

		ifstream inp("data.bin", std::ios_base::binary); // ��������� ���� data.bin �� ������
		if(d.ParseFromIstream(&inp)) {                   // ���� �������������� �������, ��
			str += d.str();                              //
			i += d.i();                                  //
			cout << str << " " << i << endl;             // ������� ����� ��������
		} else {                             // ���� �������������� �� �������
			cout << "Faled deserialize"<< endl;
		}
	} else {                                         // ���� ������������ �� �������
		out.close();
		cout << "Faled Serialize" << endl;
	}

	return 0;
}
