#include "Lib.h"
#include<direct.h>
#include"User.h"

void RusMsg(const char* message) {
	char rmessage[256];
	CharToOem(message, rmessage);
	cout << rmessage;
}

void main() {
	setlocale(LC_ALL, "rus");
	//тестирование класса USER
	User u;
	Date date1, date2;

	int key = 0;
	do { 
		system("cls");
		/*
		RusMsg("1 - регистрация нового пользователя\n");
		RusMsg("2 - вход пользователя в систему\n");
		RusMsg("0 - выход\n");*/
		cout<<"1 - регистрация нового пользователя\n"
		    <<"2 - вход пользователя в систему\n"
		    <<"0 - выход\n";
		cin >> key;
		switch (key){
		case 1: //запись
			u.set_Email ("ivan@bk.ru");
			u.set_Pass("IvaNov_2020");
			u.set_SecretWord("2020_иВАнОВ");
			u.set_FIO("Иванов И.И.");
			date1.set_Date_ddmmyyyy("20.08.1990");
			u.set_tel("066-777-66-55");
			date2; u.set_DateReg(date2);
		    u.set_rootAdmin(1);
			//u.print_User();
			u.singUp();
			break;
		case 2: //чтение
			if (u.autorization())
				u.print_User();
			break;
		}
		system("pause");
	}while (key != 0);
}
