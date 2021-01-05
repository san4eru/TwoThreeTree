#include "TempNode.h"

//setû

void TempNode::setK4(StringKey* k)
{
	k4 = k;
}

void TempNode::setBiggest(Node* node)
{
	biggest = node;

	if (node != NULL)
		node->SetParent(this);
}

//getû

StringKey* TempNode::getK4()
{
	return k4;
}

Node* TempNode::getBiggest()
{
	return biggest;
}


