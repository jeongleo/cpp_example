/*
 * Banking System Ver 0.1
 * 작성자: 정민호
 * 내 용: OPP 단계별 프로젝트의 기본 틀 구성
 * 참 고: 윤성우, 열혈 C++ 프로그래밍
 */
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

void showMenu(void);		// 메뉴출력
void makeAccount(void);		// 계좌개설을 위한 함수
void depositMoney(void);	// 입금
void withdrawMoney(void);	// 출금
void showAllAccInfo(void);	// 잔액조회

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

typedef struct
{
	int accID; // 계좌번호
	int balance; // 잔액
	char cusName[NAME_LEN]; // 고객이름
} Account;

Account accArr[100]; // Account array
int accNum = 0; // number of saved Account


int main(void)
{
	int choice;
	
	while(1)
	{
		showMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;
		
		switch(choice)
		{
			case MAKE:
				makeAccount();
				break;
			case DEPOSIT:
				depositMoney();
				break;
			case WITHDRAW:
				withdrawMoney();
				break;
			case INQUIRE:
				showAllAccInfo();
				break;
			case EXIT:
				return 0;
			default:
				cout << "Illegal selection.." << endl;
		}
	}
	return 0;
}

void showMenu()
{
	cout << endl;
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void makeAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;
	
	cout << "[계좌개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << endl;
	
	accArr[accNum].accID = id;
	accArr[accNum].balance = balance;
	strcpy(accArr[accNum].cusName, name);
	accNum++;
}

void depositMoney()
{
	int money;
	int id;
	
	cout << "[입 금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "입금액: "; cin >> money;
	
	for(int i=0; i<accNum; i++)
	{
		if(accArr[i].accID == id)
		{
			accArr[i].balance += money;
			cout << "입금완료" << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl;
}

void withdrawMoney()
{
	int money;
	int id;
	
	cout << "[출 금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "출금액: "; cin >> money;
	
	for(int i=0; i<accNum; i++)
	{
		if(accArr[i].accID == id)
		{
			if(accArr[i].balance < money)
			{
				cout << "잔액부족" << endl;
				return;
			}
			accArr[i].balance -= money;
			cout << "출금완료" << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl;
}

void showAllAccInfo()
{
	cout << "계좌ID\t\t" << "이 름\t\t" << "잔 액\t\t" << endl;
	for(int i=0; i<accNum; i++)
	{
		cout << accArr[i].accID << "\t\t";
		cout << accArr[i].cusName << "\t\t";
		cout << accArr[i].balance << endl;
	}
}