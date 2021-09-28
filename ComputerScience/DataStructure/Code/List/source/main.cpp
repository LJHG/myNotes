#include<iostream>
#include"class.cpp"
#include"project.cpp"
using namespace std;

int IO(string str);

void test1()
{
	string str = "IOIOIOIO";
	cout << IO(str);
	return;
}

int main()
{
	test1();
	return 0;
}