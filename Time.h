#pragma once
#include<ctime>
#include<iostream>

using namespace std;
class Time_{
	int h = 0;
	int m = 0;
	int s = 0;
	char* format;//am/pm (12-hours), utc (24-hours)

public:
	//---------КОНСТРУКТОРЫ и ДЕСТРУКТОР---------
	Time_() {
		tm* tim = new tm;
		time_t tt = time(NULL);
		//заполнение полей ст-ры значениями
		localtime_s(tim, &tt);
		h = tim->tm_hour;
		m = tim->tm_min;
		s = tim->tm_sec;
		format = new char[4];
		format[0] = 'u'; format[1] = 't'; format[2] = 'c'; format[3] = '\0';
	}
	Time_(int h, int m, int s, const char* format = "utc") {
		this->h = h; this->m = m; this->s = s;
		this->setFormat(format);
	}
	Time_(const Time_& obj) {
		h = obj.h; m = obj.m; s = obj.s;
		if (obj.format != NULL) {
			if (obj.format[0] == 'u') {
				this->format = new char[4];
				format[0] = 'u'; format[1] = 't'; format[2] = 'c'; format[3] = '\0';
			}
			else {
				format = new char[3];
				format[0] = obj.format[0]; format[1] = obj.format[1]; format[2] = '\0';
			}
		}
	}
	~Time_() {}
	//---------АКСЕССОРЫ---------
	void setHour(int hour) {
		h = hour;
	}
	int getHour() {
		return h;
	}
	void setMinutes(int minutes) {
		m = minutes;
	}
	int getMinutes() {
		return m;
	}
	void setSeconds(int seconds) {
		s = seconds;
	}
	int getSeconds() {
		return s;
	}
	void setFormat(const char* format) { // !!! to upTime_ time by the new format
		//попытка обойти #include<string.h>
		if (this->format == nullptr) delete[]this->format;
		if (//проверка на корректнубю подачу формата am/pm, иначе -> utc
			((format[0] == 'a' || format[0] == 'A') && (format[1] == 'a' || format[1] == 'A') && format[2] == '\0')|| 
			((format[0] == 'p' || format[0] == 'P') && (format[1] == 'm' || format[1] == 'M') && format[2] == '\0')
			)
		{
			this->format = new char[3];
			if (this->getHour() >= 0 && this->getHour() < 12) 
				this->format[0] = 'a'; 
			else 
				this->format[0] = 'p'; 
			this->format[1] = 'm'; this->format[2] = '\0';
		}
		else {
			this->format = new char[4];
			this->format[0] = 'u'; this->format[1] = 't'; this->format[2] = 'c'; this->format[3] = '\0';
		}
	}
	const char* getFormat() {
		if (!(this->format[0] == 'u')) {
			setFormat("pm");
			return this->format;
		}
		else 
			return this->format;
	}
	bool validTime(){
		if (h < 0 || h >= 24) return false;
		if (m < 0 || m >= 60) return false;
		if (s < 0 || s >= 60) return false;
		return true;
	}
	void tickTime() { //every tick add one second
		s ++;
		if (s > 59) {
			s = 0;
			m++;
		}
		if (m > 59) {
			m = 0;
			h++;
		}
		if (h > 23) {
			h = 0;
		}
	}
	void tickTimetoBack() { //every tick add one second
		s--;
		if (s < 0) {
			s = 59;
			m--;
		}
		if (m < 0) {
			m = 59;
			h--;
		}
		if (h < 0) {
			h = 23;
		}
	}
	void showTime() {
		int t=0;
		if (format[0]=='u')
			cout << h / 10 << h % 10 << ":";
		else {
			h > 12 ? t = h - 12 : t = h;
			cout << "[" << this->getFormat() << "] ";
			cout << t / 10 << t % 10 << ":";
		}
			cout<< m / 10 << m % 10 << ":"
			<< s / 10 << s % 10 << "\n";
	}
	void setTime(int h, int m, int s) {
		setHour(h); setHour(m); setHour(s);
	}
	void setNow() {
		tm* tim = new tm;
		time_t tt = time(NULL);
		//заполнение полей ст-ры значениями
		localtime_s(tim, &tt);
		h = tim->tm_hour;
		m = tim->tm_min;
		s = tim->tm_sec;
	}
	//--------- Comparison operators ---------
	bool operator == (const Time_& obj) {
		if (h == obj.h && m == obj.m && s == obj.s)return 1;
		return 0;
	}
	bool operator != (const Time_& obj) {
		if (h == obj.h && m == obj.m && s == obj.s)return 0;
		return 1;
	}
	bool operator > (const Time_& obj) {
		if (h > obj.h) return 1;
		else if (h == obj.h && m > obj.m) return 1;
		else if (h == obj.h && m == obj.m && s > obj.s) return 1;
		else return 0;
	}
	bool operator < (const Time_& obj) {
		if (h < obj.h) return 1;
		else if (h == obj.h && m < obj.m) return 1;
		else if (h == obj.h && m == obj.m && s < obj.s) return 1;
		else return 0;
	}
	bool operator >= (const Time_& obj) {
		if (h > obj.h) return 1;
		else if (h == obj.h && m > obj.m) return 1;
		else if (h == obj.h && m == obj.m && s >= obj.s) return 1;
		else return 0;
	}
	bool operator <= (const Time_& obj) {
		if (h < obj.h) return 1;
		else if (h == obj.h && m < obj.m) return 1;
		else if (h == obj.h && m == obj.m && s <= obj.s) return 1;
		else return 0;
	}
	//--------- Assignment operators ---------
	Time_& operator = (const Time_& obj) {
		h = obj.h; m = obj.m; s = obj.s;
		if (obj.format != NULL) {
			if (obj.format[0] == 'u') {
				this->format = new char[4];
				format[0] = 'u'; format[1] = 't'; format[2] = 'c'; format[3] = '\0';
			}
			else {
				format = new char[3];
				format[0] = obj.format[0]; format[1] = obj.format[1]; format[2] = '\0';
			}
		}
		return *this;
	}
	Time_& operator = (const char T[9]) {
		Time_ t; 
		char h1[3]; h1[0] = T[0]; h1[1] = T[1]; h1[2] = '\0'; t.setHour(atoi(h1));
		char m1[3]; m1[0] = T[4]; m1[1] = T[5]; m1[2] = '\0'; t.setMinutes(atoi(m1));
		char s1[3]; s1[0] = T[7]; s1[1] = T[8]; s1[2] = '\0';  t.setSeconds(atoi(s1));
		t.setFormat("utc");
		if (t.validTime()) {
			*this = t;
			return *this;
		}
		else {
			h=0; m=0; s=0;
			return *this;
		}

	}


	Time_& operator += (int n) {
		for (int i = 0; i < n; i++) {
			this->tickTime();
		}
		return *this;
	}
	Time_& operator -= (int n) {
		for (int i = 0; i < n; i++) {
			this->tickTimetoBack();
		}
		return *this;
	}
	//--------- Arithmetic operators ---------
	Time_ operator + (int n) {
		*this += n;
		return *this;
	}
	Time_ operator - (int n) {
		*this -= n;
		return *this;
	}
	Time_& operator++() {
		*this += 1;
		return *this;
	}
	Time_& operator--() {
		*this -= 1;
		return *this;
	}
	Time_ operator++(int)
	{
		Time_ tmp;
		tmp.setHour(this->getHour());
		tmp.setMinutes(this->getMinutes());
		tmp.setSeconds(this->getSeconds());
		*this += 1;
		return tmp;
	}
	Time_ operator--(int)
	{
		Time_ tmp;
		tmp.setHour(this->getHour());
		tmp.setMinutes(this->getMinutes());
		tmp.setSeconds(this->getSeconds());
		*this -= 1;
		return tmp;
	}
	friend ostream& operator<<(ostream& os, Time_& T) {
		//os << T.h/10<< T.h%10 << ':' << T.m/10 << T.m%10 << ':' << T.s / 10 << T.s % 10;
		int t = 0;
		if (T.format[0] == 'u')
			os << T.h / 10 << T.h % 10 << ':';
		else {
			T.h > 12 ? t = T.h - 12 : t = T.h; 
			os << "[" << T.getFormat() << "] ";
			os << t / 10 << t % 10 << ":";
		}
		os << T.m / 10 << T.m % 10 << ':' << T.s / 10 << T.s % 10;
		return os;
	}
	friend istream& operator>>(istream& is, Time_& T) {
		is >> T.h >> T.m>> T.s;
		return is;
	}
};
