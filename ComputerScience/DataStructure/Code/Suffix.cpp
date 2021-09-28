#include<iostream>
using namespace std;

#define MAXSIZE 20

//栈类
template<typename T>
class SqStack{
	T data[MAXSIZE];
	int length;
public:
	SqStack() {
		length = 0;
	}
	//在push元素进栈顶
	int insertElem(T e)
	{
		if (length > MAXSIZE)
			return 0;
		data[length] = e;
		length++;
		return 1;
	}
	//在pop出栈顶元素
	int deleteElem(T& e)
	{
		if (length == 0)
			return 0;
		e = data[length - 1];
		length--;
		return 1;
	}
	//获取栈顶元素
	char getElem()
	{
		if (length == 0)
			return 0;
		return data[length - 1];
	}
	//获取栈长度
	int getlength()
	{
		return length;
	}

	//依次输出栈顶到栈底元素，参数0表示默认输出，1表示逆序输出
	void coutStack(int r)
	{
		if (length == 0)
		{
			cout << "nothing" << endl;
			return;
		}
		if (r == 0)
		{
			for (int i = 0; i < length; i++)
				cout << data[i] << " ";
			cout << endl;
		}
		else if (r == 1)
		{
			for (int i = length-1; i > -1; i--)
				cout << data[i] << " ";
			cout << endl;
		}
	}
	//翻转栈内元素
	void reverse()
	{
		for (int i = 0; i <= length/2-1; i++)
		{
			T temp = data[i];
			data[i] = data[length - i - 1];
			data[length - i - 1] = temp;
		}
	}
	//将一个元素复制入栈，两个参数：待复制数组和数组长度
	int copyArray(T a[], int len)
	{
		if (length > MAXSIZE + 1)
			return 0;
		for (int i = len-1; i > -1; i--)
			insertElem(a[i]);
		return 1;
	}
};

void test1(SqStack<char> in, SqStack<char> su, SqStack<char> op)//test1
{
	cout << "中缀";
	in.coutStack(1);
	cout << "后缀";
	su.coutStack(0);
	cout << "符号";
	op.coutStack(0);
	cout << endl;
}
void test2(SqStack<char> su, SqStack<double> num)//test1
{
	cout << "后缀";
	su.coutStack(0);
	cout << "数字";
	num.coutStack(0);
	cout << endl;
}

//获取运算符优先级（'+'、'-'、'*'、'/'、'（'）
int getPriority(char op)
{
	if (op == '(')
		return 0;
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
}
//中缀表达式栈转后缀表达式栈，返回值为后缀表达式栈
SqStack<char> InfixToSuffix(SqStack<char> inffix)
{
	SqStack<char> suffix;
	SqStack<char> op;

	for (; inffix.getlength() !=0;)
	{
		//test1(inffix, suffix, op);//test

		char e;
		inffix.deleteElem(e);

		//如果是数值直接写入suffix栈中
		if (e >= '0' && e <= '9')
			suffix.insertElem(e);
		else
		{
			//如果是(直接写入op栈中
			if (e == '(')
				op.insertElem(e);
			//如果是运算符则比较优先级
			else if (e == '+' || e == '-' || e == '*' || e == '/')
			{
				for (;;)
				{
					//优先级大于当前顶端运算符优先级则直接入op栈
					if (op.getlength() == 0 ||
						getPriority(e) > getPriority(op.getElem()) ||
						op.getElem() == ')')
					{
						op.insertElem(e);
						break;
					}
					//否则将op栈顶元素移入suffix栈
					else
					{
						char top;
						op.deleteElem(top);
						suffix.insertElem(top);
					}
				}
			}
			//如果是)则一直将op栈元素移入suffix栈直到（出栈
			else if (e == ')')
			{
				for (; op.getElem() != '(';)
				{
					char top;
					op.deleteElem(top);
					suffix.insertElem(top);
				}
				char i;
				op.deleteElem(i);
			}
		}
	}
	for (; op.getlength()!=0; )
	{
		char e;
		op.deleteElem(e);
		suffix.insertElem(e);
	}

	cout << "suffix:" << endl;
	suffix.coutStack(0);//coutStack(0)顺序输出
	return suffix;
}
//后缀表达式栈求值，返回值为浮点型的结果
double CalSuffix(SqStack<char> suffix)
{
	SqStack<double> num;

	for (; suffix.getlength() != 0;)
	{
		//test2(suffix, num);//test2

		char e;
		suffix.deleteElem(e);
		if ('0' <= e && e <= '9') {
			num.insertElem((double)e-48);}
		else if (e == '+' || e == '-' || e == '*' || e == '/')
		{
			double num2;
			num.deleteElem(num2);
			double num1;
			num.deleteElem(num1);
			if (e == '+')
				num.insertElem((char)(num1 + num2));
			else if (e == '-')
				num.insertElem((char)(num1 - num2));
			else if (e == '*')
				num.insertElem((char)(num1 * num2));
			else if (e == '/')
				num.insertElem((char)(num1 / num2));
		}
	}
	return num.getElem();
}
//中缀表达式栈求值，返回值为浮点型的结果
double Calculator(SqStack<char> infix)
{
	SqStack<char> suffix = InfixToSuffix(infix);
	suffix.reverse();
	return CalSuffix(suffix);
}

int main()
{
	char a[11] = { '3','+', '4', '*', '5', '*', '(', '2', '+', '3', ')'};
	int len = 11;

	SqStack<char> test1;
	test1.copyArray(a, len);

	cout << "infix" << endl;
	test1.coutStack(1);//coutStack(1)逆序输出
	cout << Calculator(test1) << endl;


	return 0;
}