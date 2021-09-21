#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

const int MAXSIZE = 100;
class MyString;
void KMP(MyString S, MyString T);

class MyString
{
    string m_String;
    int m_Length;
    int m_Next[MAXSIZE];
    void createNextval()
    {
        m_Next[0] = -1;
        m_Next[1] = 0;
        int i = 1, t = 0;
        while (i < m_Length)
        {
            if (m_String[i] == m_String[t])
            {
                if (m_String[i + 1] != m_String[t + 1])
                    m_Next[++i] = ++t;
                else
                    m_Next[++i] = m_Next[++t];
            }
            else if (t == 0)
                m_Next[++i] = 0;
            else
                t = m_Next[t];
        }
    }

public:
    MyString(string str)
    {
        m_String = str;
        m_Length = size(str);
        createNextval();
    }
    int getLength()
    {
        return m_Length;
    }
    char getString(int i)
    {
        return m_String[i];
    }
    int getNext(int i)
    {
        return m_Next[i];
    }
};

void KMP(MyString S, MyString T)
{
    int s = 0, t = 0;
    while (s - t < S.getLength() - T.getLength())
    {
        if (t == -1 || S.getString(s) == T.getString(t))
        {
            if (t == T.getLength() - 1)
                cout << s - t << endl;;
            s++;
            t++;
        }
        else
            t = T.getNext(t);
    }
}

void test2()
{
    string t;
    t = "ababab";
    MyString T(t);
    string s;
    s = "aaabbbaababababbbaba";
    MyString S(s);
    KMP(S, T);
}

int main()
{
    test2();

    return 0;
}