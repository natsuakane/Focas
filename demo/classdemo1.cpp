#include <iostream>
class ICalc {
public:
virtual int Calclation(int a,int b) = 0;
virtual ~ICalc() {}
private:
protected:
};
class Plus : public ICalc {
public:
int Calclation(int a,int b) {
return (a + b);
};
~Plus() {
std::cout << "PlusDestructor" << std::endl;
};
private:
protected:
};
class Minus : public ICalc {
public:
int Calclation(int a,int b) {
return (a - b);
};
~Minus() {
std::cout << "MinusDestructor" << std::endl;
};
private:
protected:
};
int main() {
ICalc* calc1 = new Plus();
ICalc* calc2 = new Minus();
int result = ((*calc2).Calclation(((*calc1).Calclation(3,5)),4));
std::cout << result << std::endl;
}

