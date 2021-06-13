/*
 * Banking System Ver 0.4
 * 작성자: 정민호
 * 내 용: Account 클래스 정의, 객체 포인터 배열 적용
 * 참 고: 윤성우, 열혈 C++ 프로그래밍
 */
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

/*
 * 클래스 이름 : Account
 * 클래스 유형 : Entity 클래스
 */

class Account
{
private:
    int accID; // 계좌번호
	int balance; // 잔액
	char * cusName; // 고객이름

public:
    Account(int ID, int money, char * name);
    Account(const Account & ref);
    int getAccID() const;
    void deposit(int money);
    int withdraw(int money);
    void showAccInfo() const;
    ~Account();
};

Account::Account(int ID, int money, char * name)
    : accID(ID), balance(money)
{
    cusName = new char[strlen(name) + 1];
    strcpy(cusName, name);
}

Account::Account(const Account & ref)
    : accID(ref.accID), balance(ref.balance)
{
    cusName = new char[strlen(ref.cusName) + 1];
    strcpy(cusName, ref.cusName);
}

int Account::getAccID() const { return accID; }

void Account::deposit(int money)
{
    balance += money;
}

int Account::withdraw(int money)
{
    if(balance < money)
    {
        return 0;
    }
    balance -= money;
    return money;
}

void Account::showAccInfo() const
{
    cout << "계좌ID : " << accID << endl;
    cout << "이 름  : " << cusName << endl;
    cout << "잔 액  : " << balance << endl;
}

Account::~Account()
{
    delete []cusName;
}


/*
 * 클래스 이름 : AccountHandler
 * 클래스 유형 : 컨트롤(Control) 클래스
 */

class AccountHandler
{
private:
	Account * accArr[100]; // Account array
	int accNum; // number of saved Account
	
public:
	AccountHandler();
	void showMenu(void) const; // 메뉴출력
	void makeAccount(void); // 계좌개설을 위한 함수
	void depositMoney(void); // 입금
	void withdrawMoney(void); // 출금
	void showAllAccInfo(void) const; // 잔액조회
	~AccountHandler();

};

AccountHandler::AccountHandler() : accNum(0)
{	}

AccountHandler::~AccountHandler()
{
	for(int i=0; i<accNum; i++){
		delete accArr[i];
	}
}

void AccountHandler::showMenu() const
{
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::makeAccount()
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

void AccountHandler::depositMoney()
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

void AccountHandler::withdrawMoney()
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

void AccountHandler::showAllAccInfo() const
{
	for(int i=0; i<accNum; i++)
	{
		accArr[i]->showAccInfo();
		cout << endl;
	}
}


/*
 * 컨트롤 클래스 AccountHandler 중심으로 변경된 main 함수
 */

int main(void)
{
	AccountHandler manager;
	int choice;
	
	while(1)
	{
		manager.showMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;
		
		switch(choice)
		{
			case MAKE:
				manager.makeAccount();
				break;
			case DEPOSIT:
				manager.depositMoney();
				break;
			case WITHDRAW:
				manager.withdrawMoney();
				break;
			case INQUIRE:
				manager.showAllAccInfo();
				break;
			case EXIT:
				return 0;
			default:
				cout << "Illegal selection.." << endl;
		}
	}
	return 0;
}