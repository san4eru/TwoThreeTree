#ifndef _NODE_H_
#define _NODE_H_

#include "Template.h"

class Node
{

protected:
	
	Node *current;
	int isleaf;

public:
	 // �����������
	Node()
	{
	}

	 // ����������
	virtual ~Node()
	{
	}

	int IsLeaf(); // �����������, ��� ���� �������� �������� ��������� true. false � ��������� ������.

	//������ ���������
	void SetParent(Node* p);
	Node* getParent();	
};

#endif