#include "Template.h"

//Конструктор копирования
Template::Template(const Template& otherData)
{
	if (otherData.name != NULL)
	{
		name = new StringKey(*otherData.name);
		data =otherData.data;
	}
}



int Template::getdata()
{
	return this->data;
}

StringKey* Template::GetKey()const
{
	return name;
}

//ввод от пользователя, вернет NULL, если произошла ошибка
Template* Template::Read(ifstream& inputFile)
{
	StringKey* tempSKey;
	Template* outData;
	
	try
	{
		tempSKey= StringKey::Read(inputFile);
	}
	catch (...)
	{
		return NULL;
	}
	if (!tempSKey)
	{
		return NULL;
	}

	outData =new Template;

	outData->name=tempSKey;
	try
	{
		if (!(inputFile >> outData->data))
		{
			delete outData;

			return NULL;
		}
	}
	catch (...)
	{
		delete outData;

		return NULL;
	}
	return outData;
}

// чтение ввода с клавиатуры
Template* Template::Readfromkeyboard(string new_k, int new_data)
{
	StringKey* tempSKey = StringKey::Readfromkeyboard(new_k);

	Template* outData = new Template;

	outData->name = tempSKey;
	outData->data = new_data;

	return outData;
}