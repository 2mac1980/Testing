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
	//������������ ������ USER
	User u;
	Date date1, date2;

	int key = 0;
	do { 
		system("cls");
		/*
		RusMsg("1 - ����������� ������ ������������\n");
		RusMsg("2 - ���� ������������ � �������\n");
		RusMsg("0 - �����\n");*/
		cout<<"1 - ����������� ������ ������������\n"
		    <<"2 - ���� ������������ � �������\n"
		    <<"0 - �����\n";
		cin >> key;
		switch (key){
		case 1: //������
			u.set_Email ("ivan@bk.ru");
			u.set_Pass("IvaNov_2020");
			u.set_SecretWord("2020_������");
			u.set_FIO("������ �.�.");
			date1.set_Date_ddmmyyyy("20.08.1990");
			u.set_tel("066-777-66-55");
			date2; u.set_DateReg(date2);
		    u.set_rootAdmin(1);
			//u.print_User();
			u.singUp();
			break;
		case 2: //������
			if (u.autorization())
				u.print_User();
			break;
		}
		system("pause");
	}while (key != 0);
}
