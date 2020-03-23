#include "Date.h"

string Date::to_string(int n)
{
	ostringstream ss;
	ss << n;
	return ss.str();
}

Date::Date() {
	//получить системную дату 
   // создаем стд объект даты и времени 
	struct tm* tim = new tm;
	// определ€ем текущую млисекунду 
	time_t tt = time(NULL);
	localtime_s(tim, &tt);
	y = 1900 + tim->tm_year;
	m = 1 + tim->tm_mon;
	d = tim->tm_mday;
	
}
Date::Date(int d, int m, int y) {
	this->d = d;
	this->m = m;
	this->y = y;
}
Date::Date(const Date& obj) {
	d = obj.d;
	m = obj.m;
	y = obj.y;
}
Date::~Date() {
	
}

void Date::set_Date_ddmmyyyy(string date) {
	Date tmp; 
	int d, m, y;
	if (date.length() == 10) {//проверка на правильность вх.данных
		d = atoi(date.substr(0, 2).c_str());
		m = atoi(date.substr(3, 2).c_str());
		y = atoi(date.substr(6, 4).c_str());
		tmp.setDay(d);
		tmp.setMonth(m);
		tmp.setYear(y);
		if (tmp.validDate()) 
			*this = tmp;
	}
}

string Date::get_Date_ddmmyyyy()
{	
	string s;
	s = to_string(d / 10)+to_string(d % 10)+'.';
	s += to_string(m / 10) + to_string(m % 10) + '.';
	s += to_string(y);
	return s;
}

void Date::setDay(int d) {
	this->d = d;
}
int Date::getDay() {
	return d;
}
void Date::setMonth(int m) {
	this->m = m;
}
int Date::getMonth()
{
	return m;
}
const char* Date::getSMonth(const char* lng) {
	if (strcmp(lng, "EN") == 0) {
		switch (getMonth()) {
		case 1: return "jenuary";
		case 2: return "february";
		case 3: return "march";
		case 4: return "april";
		case 5: return "may";
		case 6: return "june";
		case 7: return "july";
		case 8: return "august";
		case 9: return "september";
		case 10: return "october";
		case 11: return "november";
		case 12: return "desember";
		default:return "Error number of month";
		}
	}
	else if (strcmp(lng, "RU") == 0) {
		switch (getMonth()) {
		case 1: return "€нварь";
		case 2: return "февраль";
		case 3: return "март";
		case 4: return "апрель";
		case 5: return "май";
		case 6: return "июнь";
		case 7: return "июль";
		case 8: return "август";
		case 9: return "сент€брь";
		case 10: return "окт€брь";
		case 11: return "но€брь";
		case 12: return "декабрь";
		default:return "Error number of month";
		}
	}
}

void Date::setYear(int y)
{
	this->y = y;
}
int Date::getYear()
{
	return y;
}

bool Date::isLeapYear()
{//проверка на высокосность
	if (y % 4 == 0) {
		if (y % 100 == 0 && y % 400 != 0) {//исключение
			return 0;
		}
		else
			return 1;
	}
	return 0;
}
void Date::nextDate() {
	if (d == monthDays()) {
		if (m == 12) {
			d = 1;
			m = 1;
			y++;
		}
		else {
			d = 1;
			m++;
		}
	}
	else
		d++;
}
void Date::prevDate() {
	if (d == 1) {
		if (m == 1) {
			y--;
			d = 31;
			m = 12;
		}
		else {
			m--;
			d = monthDays();
		}
	}
	else {
		d--;
	}
}
int Date::monthDays()
{//кол-во дней в мес€це
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		return  31;
	else if (m == 4 || m == 6 || m == 9 || m == 11)
		return 30;
	else if (m == 2) {
		return isLeapYear() ? 29 : 28;
	}
	return 0;
}

bool Date::validDate()
{
	if (y > 0 && m > 0 && m <= 12 && d > 0 && d <= monthDays())
		return true;
	return false;
}

void Date::fillDate()
{
	bool chk;
	//заполнить дату 
	do {
		chk = 1;
		cout << "¬ведите дату (yyyy m d): ";
		cin >> y;
		if ((!cin)) {
			cout << "ќшибка ввода даты.\n";
			chk = 0;
		}
		if (chk == 1) {
			cin >> m;
			if ((!cin) || m < 1 || m >12) {
				cout << "Ќедопустимое значение мес€ца! ¬вод даты придетс€ повторить.\n"; chk = 0;
			}
		}
		if (chk == 1) {
			cin >> d;
			if (d < 1 || d >monthDays()) {
				cout << "Ќедопустимое значение дн€! ¬вод даты придетс€ повторить.\n"; chk = 0;
			}
		}
		cin.clear();
		while (cin.get() != '\n');
	} while (chk == 0);
}
void Date::printDate() {
	cout << d / 10 << d % 10 << '.' << m / 10 << m % 10 << '.' << y;
}

bool Date::operator==(const Date& obj)
{
	if (d == obj.d && m == obj.m && y == obj.y)return 1;
	return 0;
}
bool Date::operator!=(const Date& obj)
{
	if (d == obj.d && m == obj.m && y == obj.y)return 0;
	return 1;
}
bool Date::operator>(const Date& obj)
{
	if (y > obj.y) return 1;
	else if (y == obj.y && m > obj.m) return 1;
	else if (y == obj.y && m == obj.m && d > obj.d) return 1;
	else return 0;
}
bool Date::operator<(const Date& obj)
{
	if (y < obj.y) return 1;
	else if (y == obj.y && m < obj.m) return 1;
	else if (y == obj.y && m == obj.m && d < obj.d) return 1;
	else return 0;
}
bool Date::operator>=(const Date& obj)
{
	if (y > obj.y) return 1;
	else if (y == obj.y && m > obj.m) return 1;
	else if (y == obj.y && m == obj.m && d >= obj.d) return 1;
	else return 0;
}
bool Date::operator<=(const Date& obj)
{
	if (y < obj.y) return 1;
	else if (y == obj.y && m < obj.m) return 1;
	else if (y == obj.y && m == obj.m && d <= obj.d) return 1;
	else return 0;
}

Date& Date::operator=(const Date& obj) {
	d = obj.d; m = obj.m; y = obj.y;
	return *this;
}
//Date& Date::operator=(const string date)
//{
//	Date tmp;
//	int d, m, y;
//	if (date.length() == 10) {//проверка на правильность вх.данных
//		d = atoi(date.substr(0, 2).c_str());
//		m = atoi(date.substr(3, 2).c_str());
//		y = atoi(date.substr(6, 4).c_str());
//		tmp.setDay(d);
//		tmp.setMonth(m);
//		tmp.setYear(y);
//		if (tmp.validDate())
//			* this = tmp;
//	}
//	return *this;
//}
Date& Date::operator+=(int n)
{
	for (int i = 0; i < n; i++) {
		this->nextDate();
	}
	return *this;
}
Date& Date::operator-=(int n) {
	for (int i = 0; i < n; i++) {
		this->prevDate();
	}
	return *this;
}
Date Date::operator+(int n) {
	*this += n;
	return *this;
}
Date Date::operator-(int n)
{
	*this -= n;
	return *this;
}
Date& Date::operator++() {
	*this += 1;
	return *this;
}
Date& Date::operator--() {
	*this -= 1;
	return *this;
}
Date Date::operator++(int)
{
	Date tmp;
	tmp.setDay(this->getDay());
	tmp.setMonth(this->getMonth());
	tmp.setYear(this->getYear());
	*this += 1;
	return tmp;
}
Date Date::operator--(int)
{
	Date tmp;
	tmp.setDay(this->getDay());
	tmp.setMonth(this->getMonth());
	tmp.setYear(this->getYear());
	*this -= 1;
	return tmp;
}
 ostream& operator<<(ostream& os, const Date& D){
	 os << D.d/10 << D.d % 10 << '.' << D.m/10<< D.m % 10 << '.' << D.y;
	 return os;
 }
 istream& operator>>(istream& is, Date& D){//dd.mm.yyyy
	//char *tmp=new char[10]; 
	//is >> tmp; 
	//char d1[2]; char m1[2]; char y1[4];
	//d1[0]= tmp[0];d1[1] = tmp[1];//day
	//D.setDay(atoi(d1));
	//m1[0] = tmp[3]; m1[1] = tmp[4];//month
	//D.setMonth(atoi(m1));
	//y1[0] = tmp[6]; y1[1] = tmp[7]; y1[2] = tmp[8]; y1[3] = tmp[9];//year
	//D.setYear(atoi(y1)); 
	//delete[]tmp;
	 is >> D.d >> D.m >> D.y;
	return is;
 }


