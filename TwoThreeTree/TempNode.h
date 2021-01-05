#ifndef _TRANS_H_
#define _TRANS_H_

#include "Node.h"
#include "InteriorNode.h"

class TempNode : public InteriorNode
{
private:
	// ������� "������ ��������"
	StringKey*k4;
	// ��������� �������, ������� ������, ��� ��� "������ �������"
	Node *biggest;
	
public:

	//�����������
	TempNode():biggest(NULL), k4(NULL)
	{
	};
	
	//����������
	~TempNode(void)
	{
	};

	//get'� � set'�
	void setK4(StringKey* k); // ������������� min4
	void setBiggest(Node* node); // ������������� ������ �������� �������

	
	StringKey* getK4(); // �������� ���4
	Node* getBiggest(); // ���������� ������ ��������
};

#endif