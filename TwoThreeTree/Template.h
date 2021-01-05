#ifndef _WORKER_H_
#define _WORKER_H_

#include "StringKey.h"

class Template
{
private:
	StringKey* name;
	int data;
public:
	// Конструктор
	Template():name(0), data(0){}

	Template(StringKey* name, int data):name(name), data(data){}

	// Деструктор
	~Template()
	{
		delete name;
	}

	Template(const Template& otherData); // Конструктор копирования. Выдает исключение, если имя другого worker является нулевым
	
	// Возвращает ключ (имя worker)
	StringKey* GetKey()const;
	
	//чтение ввода worker из файла. null, если произошла ошибка чтения
	static Template* Read(ifstream& inputFile);

	//чтение ввода worker с клавиатуры
	static Template* Readfromkeyboard(string new_k, int new_data);

	//operator << для вывода
	friend ostream& operator<<(ostream& out, const Template& data)
	{
		out << data.name->getString() << "\t" << data.data;
		return out;
	}

	
	int getdata(); // Возвращает data
};

#endif