#include "StringKey.h"

string StringKey::getString()const // ���������� str ����
{
	return strK;
}

// ���������� ���������
int StringKey::Compare(const StringKey* s)const
{
	return (strK.compare(s->strK)); 
}

// ������ �� �����
StringKey* StringKey::Read(ifstream& inputFile)
{
	string inKey;
	StringKey* outKey = NULL;

	if(inputFile >> inKey)
	{
		outKey = new StringKey(inKey);
		
		return outKey;
	}

	return NULL;
}

// ������ � ����������
StringKey* StringKey::Readfromkeyboard(string new_k)
{
	StringKey* outKey = new StringKey(new_k);

	return outKey;
}