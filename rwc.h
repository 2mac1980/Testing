#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include"Date.h"
using namespace std;
class RWC {//класс работы с тектовым файлом
	fstream fObj; 
	string file_name;
	//bool coding;//шифрование
	int key = 0;
	template <typename T>
	string to_string(T n)
	{
		ostringstream ss;
		ss << n;
		return ss.str();
	}
	char get_char(int n) {
		char c = n;
		return c;
	}
	int getType(const string s) {
		char c[1];
		c[0] = s[0];
		return atoi(c);
	}
	string code(const string word) {
		//if (coding) {
			if (key == 0) key = word.length();
			int k = key;
			string str = word;
			for (int i = 0; i < str.length(); i++) {
				str[i] += k;
				if (key>0)k++;
			}
			return str;
		//}
		return word;
	}
	string decode(string word) {
		//if (coding) {
			string str = word;
			int k = key;
			for (int i = 0; i < str.length(); i++) {
				str[i] -= k;
				if (key > 0)k++;
			}
			return str;
		//}
		return word;
	}
public:
	void set_filename(const string name) {
		string tmp = name;
		this->file_name = name;
	}
	string get_filename() {
		return file_name;
	}
	//void set_coding(bool onoff) {
	//	coding = onoff;
	//}
	/*bool isCoding() { return coding; }*/
	bool openFileToWrite() {
		fObj.open(file_name, ios::out);
		if (fObj.good()) return 1;
		return 0;
	}
	bool openFileToRead() {
		fObj.open(file_name, ios::in);
		if (fObj.good()) return 1;
		return 0;
	}
	//ЗАПИСЬ В ФАЙЛ
	template <typename T>
	void write(T field) {//шаблон для char,char*,string
		fObj << code(to_string(field)) << endl;
	}
	void write(bool field) {
		fObj << code(to_string(field)) << endl;
	}
	void write(int field) {
		fObj << code(to_string(field)) << endl;
	}
	void write(float field) {
		fObj << code(to_string(field)) << endl;
	}
	void write(Date date){
		fObj << code(date.get_Date_ddmmyyyy()) << endl;
	}
	//ЧТЕНИЕ  ИЗ ФАЙЛА
	string get_line() {
		string s;
		getline(fObj, s);
		if (key == 0) key = s.length();
		s = decode(s);
		return s;
	}
	bool read_bool() {
		return atoi(get_line().c_str());
	}
	int read_int() {
		return atoi(get_line().c_str());
	}
	float read_float() {
		string s = get_line();
		return stof(s);//для корректной работы нельзявключать setlocale
	}
	string read_string() {
		return get_line();
	}
	Date read_Date() {
		Date d;
		d.set_Date_ddmmyyyy(get_line());
		return d;
	}
	bool FileExist() {
		if (fObj.good())  return 1;
		else return 0;
	}
};

