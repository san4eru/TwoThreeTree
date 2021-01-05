#ifndef _TRANS_H_
#define _TRANS_H_

#include "Node.h"
#include "InteriorNode.h"

class TempNode : public InteriorNode
{
private:
	// минимум "самого большого"
	StringKey*k4;
	// Четвертый ребенок, который больше, чем его "Правый ребенок"
	Node *biggest;
	
public:

	//Конструктор
	TempNode():biggest(NULL), k4(NULL)
	{
	};
	
	//Диструктор
	~TempNode(void)
	{
	};

	//get'ы и set'ы
	void setK4(StringKey* k); // устанавливает min4
	void setBiggest(Node* node); // устанавливает самого большого ребенка

	
	StringKey* getK4(); // получает мин4
	Node* getBiggest(); // возвращает самого большого
};

#endif