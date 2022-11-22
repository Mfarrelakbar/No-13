#include <iostream>

using namespace std;

class bankAccount {
private:
	int accountNumber;
	double balance;
public:
	void setAccountNumber(int);
	int getAccountNumber();
	double getBalance();

	void deposit(double);
	void withdraw(double);

	void print();
	bankAccount(int, double);
};

void bankAccount::setAccountNumber(int number) {
	accountNumber = number;
}

int bankAccount::getAccountNumber() {
	return accountNumber;
}

double bankAccount::getBalance() {
	return balance;
}

void bankAccount::deposit(double amount) {
	balance += amount;
}

void bankAccount::withdraw(double amount) {
	balance -= amount;
}

void bankAccount::print() {
	cout << accountNumber << ": " << balance << "$";
}

bankAccount::bankAccount(int num, double bal) {
	accountNumber = num;
	balance = bal;
}


class checkingAccount : public bankAccount {
private:
	double interestRate, minimumBalance, serviceCharges;
public:
	void setInterestRate(double);
	double getInterestRate();

	void setMinimumBalance(double);
	double getMinimumBalance();

	void setServiceCharges(double);
	double getServiceCharges();

	void postInterest();
	bool isUnderMinimum();
	void writeACheck(double);
	void withdraw(double);

	void print();

	checkingAccount(int, double, double, double, double);
	checkingAccount();
};


void checkingAccount::setInterestRate(double rate) {
	interestRate = rate;
}

double checkingAccount::getInterestRate() {
	return interestRate;
}

void checkingAccount::setMinimumBalance(double min) {
	minimumBalance = min;
}

double checkingAccount::getMinimumBalance() {
	return minimumBalance;
}

void checkingAccount::setServiceCharges(double service) {
	serviceCharges = service;
}

double checkingAccount::getServiceCharges() {
	return serviceCharges;
}

void checkingAccount::postInterest() {
	if (isUnderMinimum()) {
		bankAccount::withdraw(serviceCharges);
	}
}

bool checkingAccount::isUnderMinimum() {
	return getBalance() < minimumBalance;
}

void checkingAccount::writeACheck(double amount) {
	withdraw(amount + serviceCharges);
}

void checkingAccount::withdraw(double amount) {
	bankAccount::withdraw((1 + interestRate) * amount);
}

void checkingAccount::print() {
	bankAccount::print();
	cout << "/" << interestRate << "/" << minimumBalance << "/" << serviceCharges << "\n";
}

checkingAccount::checkingAccount(int num, double balance, double rate, double min, double service) : bankAccount(num, balance) {
	interestRate = rate;
	minimumBalance = min;
	serviceCharges = service;
}

checkingAccount::checkingAccount() : bankAccount(0, 0) {
	interestRate = 0;
	minimumBalance = 0;
	serviceCharges = 0;
}


class savingsAccount : public bankAccount {
private:
	double interestRate;
public:
	void setInterestRate(double);
	double getInterestRate();

	void postInterest();

	void withdraw();

	void print();

	savingsAccount(int, double, double);
	savingsAccount();
};


void savingsAccount::setInterestRate(double rate) {
	interestRate = rate;
}

double savingsAccount::getInterestRate() {
	return interestRate;
}

void savingsAccount::postInterest() {
	deposit(getBalance() * interestRate);
}

void savingsAccount::print() {
	bankAccount::print();
	cout << "/" << interestRate << "\n";
}

savingsAccount::savingsAccount(int num, double bal, double rate) : bankAccount(num,bal) {
	interestRate = rate;
}

savingsAccount::savingsAccount() : bankAccount(0, 0) {
	interestRate = 0;
}
#include <iostream>


using namespace std;

int main()
{
	savingsAccount ac1(523694, 500, 0.3);
	checkingAccount ac2(57564232, 500, 0.3, 50, 5);

	ac2.postInterest();
	ac2.withdraw(50);
	ac2.writeACheck(150);
	ac2.print();

	ac1.deposit(200);
	ac1.postInterest();
	ac1.print();
}
