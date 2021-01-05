#include "Node.h"
class LeafNode : public Node
{
private:
	Template* data;
	StringKey* key;
	
public:
	// Конструктор
	LeafNode()
	{
		isleaf = true;
	}

	LeafNode(StringKey* k, Template* d);

	Template* Data()const; // Возвращает данные текущего узла
	StringKey* Key()const; // Возвращает текущий ключ узла

	~LeafNode(void)
	{
	} // Диструктор
	
};

LeafNode::LeafNode(StringKey* k, Template* d)
{
	key = d->GetKey();
	data = d;

	isleaf = true;
}

Template* LeafNode::Data()const
{
	return data;
}

StringKey* LeafNode::Key()const //вернуть ключ текущего узла
{
	return data->GetKey();
}