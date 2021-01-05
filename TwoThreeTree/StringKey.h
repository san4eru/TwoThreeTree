#ifndef _STRING_KEY_H_
#define _STRING_KEY_H_

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class StringKey
{
private:
	string strK;
	
public:
	StringKey(){}// ������ �����������
	StringKey(const StringKey& otherStringKey) // ����������� �����������
	{
		strK = otherStringKey.strK;
	}

	// �����������, ������� �������� ������
	StringKey(const string& strString)
	{
		strK=strString;
	}

	~StringKey() {} // ����������
	
	//���������� ��������� ����� 2 ��������
	int Compare(const StringKey* s)const;
	string getString()const; // ���������� str

	// ������ stringKey �� �����. null, ���� ��� ������ ��������� ������
	static StringKey* Read(ifstream& inputFile);
	// ������ � ����������
	static StringKey* Readfromkeyboard(string new_k);
};

#endif