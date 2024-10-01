#include <iostream>
using namespace std;
class Animal {
public:
virtual void Cry() = 0;
virtual int GetKind() = 0;
virtual ~Animal() {}
private:
protected:
};
class Cat : public Animal {
public:
Cat() {
cout << "mew(hello)" << endl;
};
void Cry() {
cout << "mew" << endl;
};
int GetKind() {
return 1;
};
~Cat() {
cout << "mew(bye)" << endl;
};
private:
protected:
};

