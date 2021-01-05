#include "InteriorNode.h"

InteriorNode::InteriorNode(Node *l, Node *m, Node *r, StringKey*ik1, StringKey*ik2, StringKey*ik3)
{
	k1 = ik1;
	k2 = ik2;
	k3 = ik3;
	left = l;
	mid = m;
	right = r;

	//установка родителей
	right->SetParent(this);
	left->SetParent(this);
	mid->SetParent(this);
	
	isleaf = false;
}
	
void InteriorNode::setRight(Node* node)
{
	right = node;

	if (node != NULL)
		node->SetParent(this);
}

void InteriorNode::setMid(Node* node)
{
	mid = node;

	if (node != NULL)
		node->SetParent(this);
}

void InteriorNode::setLeft(Node* node)
{
	left = node;
				
	if (node != NULL)
		node->SetParent(this);
}

Node* InteriorNode::getMid()
{
	return mid;
}

Node* InteriorNode::getRight()
{
	return right;
}



Node* InteriorNode::getLeft()
{
	return left;
}

void InteriorNode::setK1(StringKey* k)
{
	k1 = k;
}

void InteriorNode::setK2(StringKey* k)
{
	k2 = k;
}

void InteriorNode::setK3(StringKey* k)
{
	k3 = k;
}

StringKey* InteriorNode::getK1()
{
	return k1;
}
		
StringKey* InteriorNode::getK2()
{
	return k2;
}


StringKey* InteriorNode::getK3()
{
	return k3;
}