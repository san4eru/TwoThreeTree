#ifndef _WORKER_H_
#define _WORKER_H_

#include "StringKey.h"

class Template
{
private:
	StringKey* name;
	int data;
public:
	// �����������
	Template():name(0), data(0){}

	Template(StringKey* name, int data):name(name), data(data){}

	// ����������
	~Template()
	{
		delete name;
	}

	Template(const Template& otherData); // ����������� �����������. ������ ����������, ���� ��� ������� worker �������� �������
	
	// ���������� ���� (��� worker)
	StringKey* GetKey()const;
	
	//������ ����� worker �� �����. null, ���� ��������� ������ ������
	static Template* Read(ifstream& inputFile);

	//������ ����� worker � ����������
	static Template* Readfromkeyboard(string new_k, int new_data);

	//operator << ��� ������
	friend ostream& operator<<(ostream& out, const Template& data)
	{
		out << data.name->getString() << "\t" << data.data;
		return out;
	}

	
	int getdata(); // ���������� data
};

#endif