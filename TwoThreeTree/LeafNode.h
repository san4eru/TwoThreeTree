#include "Node.h"
class LeafNode : public Node
{
private:
	Template* data;
	StringKey* key;
	
public:
	// �����������
	LeafNode()
	{
		isleaf = true;
	}

	LeafNode(StringKey* k, Template* d);

	Template* Data()const; // ���������� ������ �������� ����
	StringKey* Key()const; // ���������� ������� ���� ����

	~LeafNode(void)
	{
	} // ����������
	
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

StringKey* LeafNode::Key()const //������� ���� �������� ����
{
	return data->GetKey();
}