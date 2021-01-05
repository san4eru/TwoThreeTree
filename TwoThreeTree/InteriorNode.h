#ifndef _INTERIOR_H_
#define _INTERIOR_H_

#include "Node.h"
class InteriorNode : public Node
{
protected:
	StringKey *k1, *k2, *k3;
	Node *left, *mid, *right;

public:
	// Пустой конструктор
	InteriorNode():left(NULL),mid(NULL),right(NULL),k1(NULL),k2(NULL),k3(NULL)
	{
		SetParent(NULL);
		isleaf = false;
	} 
	// Конструктор
	InteriorNode(Node *l,Node *m, Node* r, StringKey*ik1, StringKey*ik2, StringKey*ik3);
	
	virtual ~InteriorNode(void)
	{
		delete left;
		delete mid;
		delete right;
	} 		

	//set'ы и get'ы
	void setK1(StringKey* k);
	StringKey* getK1();
	void setK2(StringKey* k);
	StringKey* getK2();
	void setK3(StringKey* k);
	StringKey* getK3();
	  
	void setLeft(Node* node); 
	Node* getLeft();
	void setMid(Node* node);
	Node* getMid();
	void setRight(Node* node);
	Node* getRight();

};

#endif