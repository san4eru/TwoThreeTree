#include <fstream>
#include "Node.h"
#include "InteriorNode.h"
#include "LeafNode.h"
#include "TempNode.h"

using namespace std;

class Dictionary
{
private:
		Node* root;

		void AddChild(TempNode* trans); // добавляет 4 словарь в словарь и разделяет его так, чтобы он действовал
		TempNode* MakeTransitoryNode(InteriorNode* parent, LeafNode* child); // создает временный узел 4
	
		void freeAllElementsHelper(Node* node); // освобождает все элементы рекурсивно
		void Update(InteriorNode* node); // обновляет min1, min2, min3 узла до корня
		
		InteriorNode* FindParent(StringKey* key); // находит родителя узла
		
		void print23(ofstream &outputFile, Node* node); // рекурсивно печатает в правильном порядке
		void print23Console(Node* node);
		void counterkey(Node* node, int& count_k);
		int HeightOfTree(Node* node);
public:
	//конструктор
	Dictionary():root(0)
	{
	}

	//деструктор
	~Dictionary()
	{
		//  удалить левый, средний и правый узлы рекурсивно
		delete root; 
	}

	// Вставляет data
	int Insert(StringKey *k, Template *d);

	// Удаляет data по ключу
	Template *Delete(StringKey*k);

	// Находит data по ключу
	Template *Find(StringKey*k);

	// Находит количество ключей
	int Dictionary::CountOfKey();

	// Находит высоту
	int Dictionary::CountOfHeight();

	// Освобождает все элементы в словаре
	void FreeAllElements(); 
	// Печатает словарь в алфавитном порядке

	void PrintDictionary(ofstream &outputFile);

	void PrintDictionaryConsole();

	int IsEmpty();// Проверьте, является ли словарь пустым, если пусто, верните 1 (true), иначе верните 0 (false)
	
};


int Dictionary::Insert(StringKey* k, Template* d)
{
	if (IsEmpty())
	{
		root = new LeafNode(k, d);
	}
	else
	{
		// Если k ключ найден
		if (Find(k) != NULL)
		{
			// уже существует
			return 0;
		}
		else
		{
			//  Новый лист
			LeafNode* newleaf = new LeafNode(k, d);

			// вставка

			if (root->IsLeaf()) // только один элемент в дереве
			{
				LeafNode* leafRoot = (LeafNode*)root;
				InteriorNode* newRoot = new InteriorNode();

				// leafRoot >= new
				if (leafRoot->Key()->Compare(newleaf->Key()) > 0)
				{
					newRoot->setLeft(newleaf);
					newRoot->setK1(newleaf->Key());
					newRoot->setMid(leafRoot);
					newRoot->setK2(leafRoot->Key());
				}
				else // new >leafRoot
				{
					newRoot->setLeft(leafRoot);
					newRoot->setK1(leafRoot->Key());
					newRoot->setMid(newleaf);
					newRoot->setK2(newleaf->Key());
				}

				//обновляем корень
				root = newRoot;
			}
			else // корень не лист
			{
				InteriorNode* parent = FindParent(newleaf->Key());

				// если у родителя 2-ое детей
				if (parent->getRight() == NULL)
				{
					LeafNode* left = (LeafNode*)parent->getLeft();
					LeafNode* mid = (LeafNode*)parent->getMid();

					if (newleaf->Key()->Compare(mid->Key()) > 0) // новый лист в правом
					{
						parent->setRight(newleaf);
						parent->setK3(newleaf->Key());
						// не нужно обновлять min2 min3 - отцов "родителя"
					}
					else if (newleaf->Key()->Compare(left->Key()) > 0) // новый лист в середине
					{
						parent->setRight(mid);
						parent->setK3(mid->Key());
						parent->setMid(newleaf);
						parent->setK2(newleaf->Key());
						// не нужно обновлять min2 min3 - отцов "родителя"
					}
					else if (newleaf->Key()->Compare(left->Key()) < 0) // новый лист слева
					{
						parent->setRight(mid);
						parent->setK3(mid->Key());
						parent->setMid(left);
						parent->setK2(left->Key());
						parent->setLeft(newleaf);
						parent->setK1(newleaf->Key());
					}

					Update(parent); // Обнови всех отцов "родителя" до корня
				}
				else // у родителя 3-ое детей
				{
					TempNode* temp = MakeTransitoryNode(parent, newleaf);

					parent->setLeft(NULL);
					parent->setMid(NULL);
					parent->setRight(NULL);
					delete parent; // мы сделали временного четвертого сына из этого

					AddChild(temp);

				}
			}
		}
	}

	return 1; // хорошо
}

InteriorNode* Dictionary::FindParent(StringKey* k)
{
	Node* node = root;
	InteriorNode* Interior = (InteriorNode*)node;

	InteriorNode* parent = NULL;

	while (!node->IsLeaf())
	{
		Interior = (InteriorNode*)node;

		parent = Interior;

		// k больше чем min3
		if ((Interior->getRight() != NULL) && (k->Compare(Interior->getK3()) >= 0))
		{
			node = Interior->getRight();
		}
		else if (k->Compare(Interior->getK2()) >= 0) // k между min2 и min3
		{
			node = Interior->getMid();
		}
		else // k между min1 и min2
			node = Interior->getLeft();
	}

	return parent;
}

TempNode* Dictionary::MakeTransitoryNode(InteriorNode* parent, LeafNode* child)
{
	TempNode* retFourSons = new TempNode(); // будет вместо родителя

	LeafNode* right = (LeafNode*)parent->getRight();
	LeafNode* left = (LeafNode*)parent->getLeft();
	LeafNode* mid = (LeafNode*)parent->getMid();

	StringKey* newChildKey = child->Key();

	//случай 1: Новый - самый большой
	if (newChildKey->Compare(right->Key()) > 0)
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(mid);
		retFourSons->setRight(right);
		retFourSons->setBiggest(child);
		retFourSons->setK1(left->Key());
		retFourSons->setK2(mid->Key());
		retFourSons->setK3(right->Key());
		retFourSons->setK4(child->Key());
	}
	//случай 2: Новый - между 3 и 4
	else if (newChildKey->Compare(mid->Key()) > 0)
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(mid);
		retFourSons->setRight(child);
		retFourSons->setBiggest(right);
		retFourSons->setK1(left->Key());
		retFourSons->setK2(mid->Key());
		retFourSons->setK3(child->Key());
		retFourSons->setK4(right->Key());
	}
	//случай 3: Новый - между 2 и 3
	else if (newChildKey->Compare(left->Key()) > 0) // новый 2/4
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(child);
		retFourSons->setRight(mid);
		retFourSons->setBiggest(right);
		retFourSons->setK1(left->Key());
		retFourSons->setK2(child->Key());
		retFourSons->setK3(mid->Key());
		retFourSons->setK4(right->Key());
	}
	else
	{
		retFourSons->setLeft(child);
		retFourSons->setMid(left);
		retFourSons->setRight(mid);
		retFourSons->setBiggest(right);
		retFourSons->setK1(child->Key());
		retFourSons->setK2(left->Key());
		retFourSons->setK3(mid->Key());
		retFourSons->setK4(right->Key());
	}

	if (parent != root)
	{
		InteriorNode* FatherOfParent = (InteriorNode*)parent->getParent(); // отец retFourSons (= родитель, но с 4 сыновьями)

		retFourSons->SetParent(FatherOfParent);

		if (FatherOfParent->getLeft() == parent)//родитель - левый узел
			FatherOfParent->setLeft(retFourSons);
		else if (FatherOfParent->getMid() == parent)//родитель - средний узел
			FatherOfParent->setMid(retFourSons);
		else if (FatherOfParent->getRight() == parent)//родитель - правый узел
			FatherOfParent->setRight(retFourSons);

		Update(FatherOfParent);
	}
	return retFourSons;
}

void Dictionary::Update(InteriorNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		if (node->getLeft()->IsLeaf())//сыновья листья
		{
			// Обновление на один шаг выше листьев
			node->setK1(((LeafNode*)node->getLeft())->Key());

			if (node->getMid() != NULL)
			{
				node->setK2(((LeafNode*)node->getMid())->Key());
			}
			else
			{
				node->setK2(NULL);
			}

			if (node->getRight() != NULL)
			{
				node->setK3(((LeafNode*)node->getRight())->Key());
			}
			else
			{
				node->setK3(NULL);
			}

			node = ((InteriorNode*)node->getParent());
		}

		// обновление цикла, до корня
		while (node != NULL)
		{
			node->setK1(((InteriorNode*)node->getLeft())->getK1());

			if (node->getMid() != NULL)
			{
				node->setK2(((InteriorNode*)node->getMid())->getK1());
			}
			else
			{
				node->setK2(NULL);
			}

			if (node->getRight() != NULL)
			{
				node->setK3(((InteriorNode*)node->getRight())->getK1());
			}
			else
			{
				node->setK3(NULL);
			}

			if (node == root)
			{
				node = NULL;
			}
			else
			{
				node = ((InteriorNode*)node->getParent());
			}

		}
	}
}

void Dictionary::AddChild(TempNode* trans)
{
	InteriorNode* rightMostInterior = new InteriorNode;

	rightMostInterior->setLeft(trans->getRight());
	rightMostInterior->setMid(trans->getBiggest());
	rightMostInterior->setK1(trans->getK3());
	rightMostInterior->setK2(trans->getK4());

	InteriorNode* leftMostInterior = new InteriorNode;

	leftMostInterior->setLeft(trans->getLeft());
	leftMostInterior->setMid(trans->getMid());
	leftMostInterior->setK1(trans->getK1());
	leftMostInterior->setK2(trans->getK2());

	if (trans->getParent() == NULL)
	{
		InteriorNode* parent = new InteriorNode;

		parent->setLeft(leftMostInterior);
		parent->setMid(rightMostInterior);
		parent->setK1(leftMostInterior->getK1());
		parent->setK2(rightMostInterior->getK1());

		root = parent;

		trans->setLeft(NULL);
		trans->setMid(NULL);
		trans->setRight(NULL);
		trans->setBiggest(NULL);
		delete trans;
	}
	else // переходной узел - не корень
	{
		InteriorNode* parent = (InteriorNode*)trans->getParent();

		if (parent->getRight() == NULL) // Родитель имеет 2-ух детей. Это нормально, чтобы добавить
		{
			if (trans == parent->getLeft()) // узел 4-сына является наименьшим из двух
			{
				parent->setRight(parent->getMid());
				parent->setLeft(leftMostInterior);
				parent->setMid(rightMostInterior);
			}
			else if (trans == parent->getMid())
			{
				parent->setMid(leftMostInterior);
				parent->setRight(rightMostInterior);
			}

			// обновление min1 min2 min3 до корня
			Update(parent);
		}
		else // родитель уже имеет 3-ех детей. Сделать 4-ого сына - переходным узлом
		{
			TempNode* tmpFather = new TempNode;

			if (trans == parent->getLeft())
			{
				tmpFather->setLeft(leftMostInterior);
				tmpFather->setMid(rightMostInterior);
				tmpFather->setRight(parent->getMid());
				tmpFather->setBiggest(parent->getRight());

				tmpFather->setK1(leftMostInterior->getK1());
				tmpFather->setK2(rightMostInterior->getK1());
				tmpFather->setK3(((InteriorNode*)parent->getMid())->getK1());
				tmpFather->setK4(((InteriorNode*)parent->getRight())->getK1());
			}
			else if (trans == parent->getMid())
			{
				tmpFather->setLeft(parent->getLeft());
				tmpFather->setMid(leftMostInterior);
				tmpFather->setRight(rightMostInterior);
				tmpFather->setBiggest(parent->getRight());

				tmpFather->setK1(((InteriorNode*)parent->getLeft())->getK1());
				tmpFather->setK2(leftMostInterior->getK1());
				tmpFather->setK3(rightMostInterior->getK1());
				tmpFather->setK4(((InteriorNode*)parent->getRight())->getK1());
			}
			else if (trans == parent->getRight())
			{
				tmpFather->setLeft(parent->getLeft());
				tmpFather->setMid(parent->getMid());
				tmpFather->setRight(leftMostInterior);
				tmpFather->setBiggest(rightMostInterior);

				tmpFather->setK1(((InteriorNode*)parent->getLeft())->getK1());
				tmpFather->setK2(((InteriorNode*)parent->getMid())->getK1());
				tmpFather->setK3(leftMostInterior->getK1());
				tmpFather->setK4(rightMostInterior->getK1());
			}

			InteriorNode* FatherOfParent = (InteriorNode*)parent->getParent();
			tmpFather->SetParent(parent->getParent());

			if (FatherOfParent != NULL) // если родитель не корень.
			{
				if (FatherOfParent->getLeft() == parent)//родитель - левый узел
					FatherOfParent->setLeft(tmpFather);
				else if (FatherOfParent->getMid() == parent)//родитель - средний узел
					FatherOfParent->setMid(tmpFather);
				else if (FatherOfParent->getRight() == parent)//родитель - правый узел
					FatherOfParent->setRight(tmpFather);

				Update(FatherOfParent); // обновить отца нашего переходного узла до корня
			}
			else // родитель был корнем
			{
				root = tmpFather;
			}

			parent->setLeft(NULL);
			parent->setMid(NULL);
			parent->setRight(NULL);
			delete parent; // мы поменяли родителя с нашим новым tmpFather

			trans->setLeft(NULL);
			trans->setMid(NULL);
			trans->setRight(NULL);
			trans->setBiggest(NULL);
			delete trans; // переходной узла был заменен двумя сыновьями

			// Теперь у нас есть узел с 4 сыновьями. Плохо. Нужно вызвать "добавить ребенка" рекурсивно
			AddChild(tmpFather);
		}
	}
}

Template* Dictionary::Delete(StringKey* k)
{
	Template* retWorkerDeleted = Find(k);

	if (retWorkerDeleted == NULL)
	{
		return NULL;
	}
	else
	{
		InteriorNode* parent = FindParent(k);

		if (parent == NULL) // лист был корневым => сделать пустой словарь
		{
			delete root;
			root = NULL;
		}
		else
		{
			LeafNode* leafToDel;

			// сын которого удалили
			if (parent->getK1()->Compare(k) == 0)
			{
				leafToDel = (LeafNode*)parent->getLeft();

				parent->setLeft(parent->getMid()); // сдвигаем все влево
				if (parent->getRight() != NULL)
				{
					parent->setMid(parent->getRight());
					parent->setRight(NULL);
				}
				else
				{
					parent->setMid(NULL);
				}
			}
			else if (parent->getK2()->Compare(k) == 0)
			{
				leafToDel = (LeafNode*)parent->getMid();

				//3 сына
				if (parent->getRight() != NULL)
				{
					parent->setMid(parent->getRight());
					parent->setRight(NULL);
				}
				//2 сына
				else
				{
					parent->setMid(NULL);
				}
			}
			else if ((parent->getRight() != NULL) && (parent->getK3()->Compare(k) == 0))
			{
				leafToDel = (LeafNode*)parent->getRight();

				parent->setRight(NULL);
			}

			delete leafToDel;

			Update(parent);
			// исправить неправивльные узлы
			while ((parent != NULL) && (!parent->IsLeaf()) && ((InteriorNode*)parent->getMid() == NULL))
			{
				//нет родителя
				if (parent->getParent() == NULL)
				{
					root = parent->getLeft();

					parent->setLeft(NULL);
					parent->setMid(NULL);
					parent->setRight(NULL);
					delete parent;

					if (!root->IsLeaf())
					{
						parent = (InteriorNode*)root; // начать следующую итерацию
					}
					else
					{
						parent = NULL;
					}
				}
				else // есть родитель для родителя
				{
					InteriorNode* grandpa = (InteriorNode*)parent->getParent();

					InteriorNode* leftSibling = (InteriorNode*)grandpa->getLeft();
					InteriorNode* midSibling = (InteriorNode*)grandpa->getMid();
					InteriorNode* rightSibling = (InteriorNode*)grandpa->getRight();


					if (leftSibling == parent)
					{
						//возьмем левого сына
						if (midSibling->getRight() != NULL)
						{
							leftSibling->setMid(midSibling->getLeft());

							// сдвиг левого на середину
							midSibling->setLeft(midSibling->getMid());
							midSibling->setMid(midSibling->getRight());
							midSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						// средний справа имеет двух сыновей. дать ему один и поставить его слева
						else
						{
							midSibling->setRight(midSibling->getMid());
							midSibling->setMid(midSibling->getLeft());
							midSibling->setLeft(leftSibling->getLeft());

							leftSibling->setLeft(NULL);
							leftSibling->setMid(NULL);
							leftSibling->setRight(NULL);
							delete leftSibling;

							grandpa->setLeft(midSibling);//сдвиг влево
							grandpa->setMid(rightSibling);
							grandpa->setRight(NULL);

							Update(midSibling);
							Update(rightSibling);

							parent = grandpa; // для следующей итерации
						}
					}
					else if (midSibling == parent)
					{
						if (leftSibling->getRight() != NULL) // Левый слева имеет 3 сына. возьмем его правого сына.
						{
							midSibling->setMid(midSibling->getLeft());
							midSibling->setLeft(leftSibling->getRight());

							leftSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						else // Левый налево, 2-ое сыновей. дать ему один и поставить его справа
						{
							leftSibling->setRight(midSibling->getLeft());

							midSibling->setLeft(NULL);
							midSibling->setMid(NULL);
							midSibling->setRight(NULL);
							delete midSibling;

							grandpa->setMid(rightSibling);//сдвиг влево
							grandpa->setRight(NULL);

							Update(leftSibling);
							Update(rightSibling);
							parent = grandpa; // для следующей итерации
						}
					}
					else if (rightSibling == parent)
					{
						if (midSibling->getRight() != NULL) //Средний налево имеет 3 сына. возьми его правого сына.
						{
							rightSibling->setMid(rightSibling->getLeft());
							rightSibling->setLeft(midSibling->getRight());

							midSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						else // Средний налево имеет 2 сына. дать ему один и поставить его справа
						{
							midSibling->setRight(rightSibling->getLeft());

							rightSibling->setLeft(NULL);
							rightSibling->setMid(NULL);
							rightSibling->setRight(NULL);

							// сейчас правый брат - пуст
							delete rightSibling;

							grandpa->setRight(NULL);

							Update(midSibling);
							Update(leftSibling);

							parent = grandpa; // для следующей итерации
						}
					}
				}
			} // конец while 
		}
	}

	return retWorkerDeleted;
}

void Dictionary::PrintDictionary(ofstream& outputFile)
{
	if (IsEmpty()) // если пустое
	{
		outputFile << "Дерево пустое!" << endl;
		outputFile.flush();
	}
	else
	{
		print23(outputFile, root);
	}
}

void Dictionary::print23(ofstream& outputFile, Node* node)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		LeafNode* leaf = (LeafNode*)node;
		outputFile << *(leaf->Data()) << endl;
		outputFile.flush();
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		// Распечатать в правильном порядке
		print23(outputFile, interior->getLeft());
		print23(outputFile, interior->getMid());
		print23(outputFile, interior->getRight());
	}
}

void Dictionary::PrintDictionaryConsole()
{
	if (IsEmpty()) // пустой 
		cout << "Дерево пустое!" << endl;
	else
		print23Console(root);
}

void Dictionary::print23Console(Node* node)
{
	if (node == NULL)
		return;

	if (node->IsLeaf())
	{
		LeafNode* leaf = (LeafNode*)node;
		cout << *(leaf->Data())<< endl;
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		print23Console(interior->getLeft());
		print23Console(interior->getMid());
		print23Console(interior->getRight());
	}
}

void Dictionary::FreeAllElements()
{
	freeAllElementsHelper(root); // Начать с корня
}
void Dictionary::freeAllElementsHelper(Node* node)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		LeafNode* leaf = (LeafNode*)node;

		delete leaf->Data(); // worker's dtor удаляет имя (StringKey)

		delete leaf;
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		// удалить его левого, среднего и правого сыновей рекурсивно

		freeAllElementsHelper(interior->getLeft());
		freeAllElementsHelper(interior->getMid());
		freeAllElementsHelper(interior->getRight());

		if (interior == root)
		{
			root = NULL;
		}

		interior->setLeft(NULL);
		interior->setMid(NULL);
		interior->setRight(NULL);
		delete interior;
	}
}

int Dictionary::IsEmpty()// Проверьте, является ли словарь пустым, если пусто, верните 1 (true), иначе верните 0 (false)
{
	return (root == NULL);
}

Template* Dictionary::Find(StringKey* k)
{
	//случай 1: словарь пуст или k равен нулю, возврат без поиска
	if (IsEmpty() || k == NULL)
	{
		return NULL;
	}

	InteriorNode* Interior;
	Node* node = root;

	while (!node->IsLeaf())
	{
		Interior = (InteriorNode*)node;

		// k >= min3
		if ((Interior->getRight() != NULL) && (k->Compare(Interior->getK3()) >= 0))
		{
			node = Interior->getRight();
		}
		// k >= min2 && k < min3
		else if (k->Compare(Interior->getK2()) >= 0)
		{
			node = Interior->getMid();
		}
		// k <min2
		else
			node = Interior->getLeft();
	}

	// лист
	LeafNode* leaf = (LeafNode*)node;

	if (k->Compare(leaf->Key()) == 0)
		return leaf->Data();
	else
		return NULL;

}

int Dictionary::CountOfKey()
{
	int count_k = 0;
	//если словарь пуст, то возврат без подсчета
	if (IsEmpty())
		return 0;
	else
	{
		counterkey(root, count_k);
	}

	return count_k;
}

void Dictionary::counterkey(Node* node, int &count_k)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		count_k++;
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		counterkey(interior->getLeft(), count_k);
		counterkey(interior->getMid(), count_k);
		counterkey(interior->getRight(), count_k);
	}
}

int Dictionary::CountOfHeight()
{
	int count_h = 0;
	//если словарь пуст, то возврат без подсчета
	if (IsEmpty())
		return 0;
	else
	{
		count_h = HeightOfTree(root);
	}

	return count_h;
}

int Dictionary::HeightOfTree(Node* node)
{
	if (node == NULL)
		return 0;

	InteriorNode* interior = (InteriorNode*)node;
	int left, right;
	if (!node->IsLeaf()) {
		left = HeightOfTree(interior->getLeft());
	}
	else
		left = -1;
	if (!node->IsLeaf()) {
		right = HeightOfTree(interior->getRight());
	}
	else
		right = -1;
	int max = left > right ? left : right;
	return max + 1;
}