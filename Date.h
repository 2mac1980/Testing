#pragma once
#include<time.h>
#include<string.h>
#include<iostream>
#include <sstream>
using namespace std;

class Date{
	int d; int m; int y;
	//по свободе накидать формат даты
	string to_string(int n);
	
public:
	//---------КОНСТРУКТОРЫ---------
	Date();
	Date(int d, int m, int y);
	Date(const Date& obj);
	//---------ДЕСТРУКТОР-----------
	~Date();
	//---------АКСЕССОРЫ------------
	void set_Date_ddmmyyyy(string date);
	string get_Date_ddmmyyyy();
	void setDay(int d);
	int getDay();
	
	void setMonth(int d);
	int getMonth();
	const char* getSMonth(const char* = "EN");
	
	void setYear(int d);
	int getYear();
	//----------ФУНКЦИИ-ЧЛЕНЫ(МЕТОДЫ)--------
	bool validDate();
	
		
	void fillDate();
	void printDate();
	//--------- ОПЕРАТОРЫ СРАВНЕНИЯ ---------
	bool operator == (const Date& obj);
	bool operator != (const Date& obj);
	bool operator > (const Date& obj);
	bool operator < (const Date& obj);
	bool operator >= (const Date& obj);
	bool operator <= (const Date& obj);
	//--------- ОПЕРАТОРЫ ПРИСВОЕНИЯ ---------
	Date& operator = (const Date& obj);
	//Date& operator = (const string date);
	Date& operator += (int n);
	Date& operator -= (int n);

	//------ АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ --------
	Date operator + (int n);
	Date operator - (int n);
	Date& operator++();
	Date& operator--();
	Date operator++(int);
	Date operator--(int);
	friend ostream& operator<<(ostream& os, const Date& D);
	friend istream& operator>> (istream& is, Date& D);
private:
	int monthDays();//кол-во дней в месяце
	bool isLeapYear();//проверка на высокосность
	void nextDate(); //Следующая дата
	void prevDate(); //Предыдущая дата
};
