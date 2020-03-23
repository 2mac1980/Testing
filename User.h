#pragma once
#include<iostream>
#include<string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include"rwc.h"

class User {
	string email; //Email = login
	string pass;//������
	string secretword;//��������� � ������
	string FIO;//���
	Date birth;//���� ��������
	string tel;//����.�������
	Date dateReg;//���� �����������
	bool isAdmin=false;//true - ����� ������

	RWC rw;//������ ��� ������������ ������/������ � ����
public:	
	User();
	User(User&obj);
	~User();
	//_____________������_________________//
	void set_Email(const string email);
	void set_Pass(const string pass);
	void set_SecretWord(const string word);
	void set_FIO(const string FIO);
	void set_Birth(const Date date);
	void set_tel(const string tel);
	void set_DateReg(const Date date);
	void set_rootAdmin(const bool bit);

	//_____________������_________________//
	const string get_Email();
	const string get_pass();
	const string get_pass(const string secretWord);
	const string get_SecretWord();
	const string get_FIO();
	const Date get_Birth();
	const string get_Tel();
	const Date get_DateReg();
	const bool get_rootAdmin();

	//_________������ � �������___________//

	bool validEmail(string email);//�������� �� ����������
	int passwordComplexity(const string pass);//������� ������������ ������ 0-3
	bool check_unique(string email);
	bool toFile(const string nameFile);
	bool fromFile(const string nameFile);
	bool singUp();
	bool isTruePass(const string pass);
	bool singIn(const string email);
	bool autorization();
	void print_User();
	User& operator = (const User& obj);

private:
	void codePassword(const string pass);
	const string decodePassword();
	vector<string> getUsersArr(int& N_file);
	const string set_FileName();
	const string set_FileName(string email);
};