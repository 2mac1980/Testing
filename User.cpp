#include "User.h"

User::User(){


}
User::User(User& obj){
	email = obj.email;
	pass = obj.pass;
	secretword = obj.secretword;
	FIO = obj.FIO;
	birth = obj.birth;
	tel = obj.tel;
	dateReg = obj.dateReg;
	isAdmin = obj.isAdmin;
}
User::~User(){

}
//_____________СЕТЕРЫ_________________//
void User::set_Email(const string email){
	if (validEmail(email)) 
		this->email = email;
}
void User::set_Pass(const string pass){
	if (email.length() > 0) {
		codePassword(pass);
	}
}
void User::set_SecretWord(const string word){
	secretword = word;
}
void User::set_FIO(const string FIO){
	this->FIO = FIO;
}
void User::set_Birth(const Date date){
	this->birth = date;
}
void User::set_tel(const string tel){
	this->tel = tel;
}
void User::set_DateReg(const Date date){
	this->dateReg = date;
}
void User::set_rootAdmin(const bool bit){
	isAdmin = bit;
}

//_____________ГЕТЕРЫ_________________//
const string User::get_Email(){
	return email;
}
const string User::get_pass(){
	return decodePassword();
}
const string User::get_pass(const string secretWord) {
	if (this->secretword == secretWord)
		return decodePassword();
	else return "Секретное слово не верно!";
}
const string User::get_SecretWord(){
	return secretword;
}
const string User::get_FIO(){
	return FIO;
}
const Date User::get_Birth(){
	return birth;
}
const string User::get_Tel(){
	return tel;
}

const Date User::get_DateReg(){
	return dateReg;
}
const bool User::get_rootAdmin(){
	return isAdmin;
}

//_________МЕТОДЫ И ФУНКЦИИ___________//
bool User::validEmail(string email){
	int SIZE =email.length();

	int dog = 0, dot = 0, dog_i = -1;
	//часть до @ 
	for (int i = 0; i < SIZE; i++) {//
		if (email[i] == ' ') return 0;
		if (email[i] == '@') {
			if (i == 0 || i > SIZE - 3)  return 0;
			dog++; dog_i = i;
			if (dog_i > 64) return 0;//login должен быть до 64 символов
		}
	}
	if (dog != 1)return 0;
	//часть после @
	if (email[dog_i + 1] == '.') return 0;


	int dot_i = -1;
	int cnt_dot = 0;
	for (int i = dog_i + 1; i < SIZE - 1; i++) {
		if (email[i] == '.')cnt_dot++;
	}
	if (cnt_dot != 1) return 0;

	for (int i = dog_i + 1; i < SIZE - 1; i++) {
		if (email[i] == '@' || (!(email[i] >= '0' && email[i] <= '9') && !(email[i] >= 'a' &&
			email[i] <= 'z') && !(email[i] == '-') && !(email[i] == '.'))) return 0;//больше никаких @, только a..z 0..9
		if (email[i] == '.') {
			dot++; dot_i = i;
			if (dot != 1 || dot_i == SIZE - 2)
				return 0;
		}
	}

	return 1;
}
int User::passwordComplexity(const string pass){
	int id = 0; bool isA = 0, isU = 0, isL = 0;
	int SIZE = pass.length();
	if (SIZE > 5) id++;
	for (int i = 0; i < SIZE; i++) {
		if (isalpha(pass[i])) {
			isA = 1;
			if (isupper(pass[i])) isU = 1;
			if (!isupper(pass[i])) isL = 1;
		}
	}
	if (isA) id++; if (isU && isL)id++;
	return id;
}
//шифровка от длины логина
void User::codePassword(const string pass) {
	int x = email.length();
	string str = pass;
	for (int i = 0; i < str.length(); i++) {
		str[i] += x;
	}
	this->pass = str;
}
const string User::decodePassword() {
	int x = email.length();
	string str = pass;
	for (int i = 0; i < str.length(); i++) {
		str[i] -= x;
	}
	return str;
}
vector<string> User::getUsersArr(int& N_file){
	WIN32_FIND_DATA FindFileData;
	vector<string> fileArr;
	
	HANDLE hf = FindFirstFile("Users\\*.user", &FindFileData);
	if (hf == INVALID_HANDLE_VALUE) {
		fileArr.push_back("Ошибка поиска файла.");
	}
	else {
		do {
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				fileArr.push_back(FindFileData.cFileName);
				N_file++;
				//fileArr = FilesNameArr(fileArr, N_file);
				//strcpy(fileArr[N_file - 1], FindFileData.cFileName);
			}
		} while (FindNextFile(hf, &FindFileData));
	}
	return fileArr;
}
const string User::set_FileName(){
	
	string filename = "Users\\" + email + ".user";
	return filename;
	
}
const string User::set_FileName(string email) {

	string filename = "Users\\" + email + ".user";
	return filename;

}
bool User::check_unique(string email){
	int n=0;
	/*string tst1, tst2;*/
	vector < string > vect=getUsersArr(n);
	for (int i = 0; i < n; i++){
		/*tst1 = "Users\\" + vect[i];
		tst2 = email + ".user";*/
		if ("Users\\"+vect[i] == email) 
			return 0;
	}
	return 1;
}
bool User::toFile(const string nameFile){
	rw.set_filename(nameFile);
	rw.openFileToWrite();
	if (!rw.FileExist()) {
		cout << "Ошибка при открытии файла.\n";
		return 0;
	}
	rw.write(email);
	rw.write(pass);
	rw.write(secretword);
	rw.write(FIO);
	rw.write(birth);
	rw.write(tel);
	rw.write(dateReg);
	rw.write(isAdmin);
	return 1;

}
bool User::fromFile(const string nameFile)
{
	rw.set_filename(nameFile);
	rw.openFileToRead();
	if (!rw.FileExist()) {
		cout << "Ошибка при открытии файла.\n";
		return 0;
	}
	email = rw.read_string();
	pass = rw.read_string();
	secretword = rw.read_string();
	FIO = rw.read_string();
	birth = rw.read_Date();
	tel = rw.read_string();
	dateReg = rw.read_Date();
	isAdmin = rw.read_bool();
	return 1;
}
bool User::singUp(){
	string filename = set_FileName();
	if (check_unique(email)) 
		return toFile(filename);
	else
		cout << "Пользователь с Email "<<email<<" уже существует.\n";
	return 0;
}
bool User::isTruePass(const string pass) {
	if (pass == decodePassword()) return 1;
	return 0;
}
bool User::singIn(const string email){
	string filename = set_FileName(email);
	if (!check_unique(filename)) {
		fromFile(filename);
		return 1;
	}
	return 0;
}

bool User::autorization()
{
	int i = 0;
	string e, p;
	/*cout << "Введите Email регистрации (он же логин): ";
	cin>>e;*/e = "ivan@bk.ru";
	if (singIn(e)) {
		for (int i = 0; i < 3; i++)//три попытки на ввод пароля
		{
			/*cout << "Введите пароль для входа в систему: ";
			cin >> p;*/p = "IvaNov_2020";
			if (isTruePass(p)) {
				cout << FIO + ", добро пожаловать в программу проверки знаний!\n\n"; cin.get();
				//cout << ", добро пожаловать в программу проверки знаний!\n\n"; cin.get();
				return 1;
			}
			else {
				cout << "Пароль не верный!\n"; cin.get();
			}
		}
	}
	else
		cout << "Пользователь с таким email не зарегистрирован!";
	return 0;
}


void User::print_User()
{
	cout << "____ИНФОРМАЦИЯ О ПОЛЬЗОВАТЕЛЕ____\n";
	cout << "Email:\t\t\t" << email << endl;
	cout << "Pass:\t\t\t" << decodePassword()<< endl;
	cout << "Секр.слово:\t\t" << secretword << endl;
	cout << "ФИО:\t\t\t" << FIO << endl;
	cout << "Дата рождения:\t\t"; birth.printDate(); cout << endl;
	cout << "Телефон:\t\t" << tel << endl;
	cout << "Дата регистрации:\t"; dateReg.printDate(); cout << endl;
	cout << "Права:\t\t\t"; (isAdmin)?cout<<"admin"<<endl: cout << "user"<<endl;
}
User& User::operator=(const User& obj){
	email = obj.email;
	pass = obj.pass;
	secretword = obj.secretword;
	FIO = obj.FIO;
	birth = obj.birth;
	tel = obj.tel;
	dateReg = obj.dateReg;
	isAdmin = obj.isAdmin;
	return*this;
}


