/*
 * Banking System Ver 0.2
 * 작성자: 정민호
 * 내 용: Account 클래스 정의, 객체 포인터 배열 적용
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


class Account
{
private:
    int accID; // 계좌번호
	int balance; // 잔액
	char * cusName; // 고객이름

public:
    Account(int ID, int money, char * name)
        : accID(ID), balance(money)
    {
        cusName = new char[strlen(name) + 1];
        strcpy(cusName, name);
    }
    
    Account(const Account & ref)
        : accID(ref.accID), balance(ref.balance)
    {
        cusName = new char[strlen(ref.cusName) + 1];
        strcpy(cusName, ref,cusName);
    }
    
    int getAccID()
    {
        return accID;
    }
    
    void deposit(int money)
    {
        balance += money;
    }
    
    int withdraw(int money)
    {
        if(balance < money)
        {
            return 0;
        }
        balance -= money;
        return money;
    }
    
    void showAccInfo()
    {
        cout << "계좌ID : " << accID << endl;
        cout << "이 름  : " << cusName << endl;
        cout << "잔 액  : " << balance << endl;
    }
    
    ~Account()
    {
        delete []cusName;
    }
};


Account * accArr[100]; // Account array
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
			    for(int i=0; i<accNum; i++)
			    {
			        delete accArr[i];
			    }
				return 0;
			default:
				cout << "Illegal selection.." << endl;
		}
	}
	return 0;
}

void showMenu()
{
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
	
	accArr[accNum++] = new Account(id, balance, name);
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
		if(accArr[i]->getAccID() == id)
		{
			accArr[i]->deposit(money);
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
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
		if(accArr[i]->getAccID() == id)
		{
			if(accArr[i]->withdraw(money) == 0)
			{
				cout << "잔액부족" << endl << endl;
				return;
			}
			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID 입니다." << endl << endl;
}

void showAllAccInfo()
{
	for(int i=0; i<accNum; i++)
	{
		accArr[i]->showAccInfo();
		cout << endl;
	}
}
