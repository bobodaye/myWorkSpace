#include <iostream>
using namespace std;

class GimmeStrategy {
protected:
	GimmeStrategy* successor = nullptr;
public:
	void setSuccessor(GimmeStrategy* _successor)
	{
		successor = _successor;
	}
	virtual void canIHave(int request) = 0;
	virtual ~GimmeStrategy() {}
};

class AskMom : public GimmeStrategy {
public:
	void canIHave(int request) 
	{
		if (0 <= request && request < 10) {
			cout << "Mooom? Can I have this?" << endl;
		}
		else if (this->successor != nullptr) {
			successor->canIHave(request);
		}
    }
};

class AskDad : public GimmeStrategy {
public:
  void canIHave(int request) {
    if (10 <= request && request < 20) {
			cout << "Dad, I really need this!" << endl;
		}
		else if (this->successor != nullptr) {
			successor->canIHave(request);
		}
  }
};

class AskGrandpa : public GimmeStrategy {
public:
	void canIHave(int request) {
	if (20 <= request && request < 30) {
		cout << "Grandpa, is it my birthday yet?" << endl;
	}
	else if (this->successor != nullptr) {
		successor->canIHave(request);
	}
  }
};

class AskGrandma : public GimmeStrategy {
public:
  void canIHave(int request) {
    
    if (30 <= request && request < 40) {
			cout << "Grandma, I really love you!" << endl;
		}
		else if (this->successor != nullptr) {
			successor->canIHave(request);
		}
  }
};

int main() 
{
	AskMom askMom;
	AskDad askDad;
	AskGrandpa askGrandpa;
	AskGrandma askGrandma;

	askMom.setSuccessor(&askDad);
	askDad.setSuccessor(&askGrandpa);
	askGrandpa.setSuccessor(&askGrandma);

	askMom.canIHave(29);

	return 0;
}
