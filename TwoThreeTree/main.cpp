#include <fstream>
#include <sstream>
#include <time.h>
#include "Dictionary.h"

using namespace std;

bool ConvertStringToInt(const string& s, unsigned int& num);
string generateRandomString();

int main()
{
	setlocale(LC_ALL, "Russian");

	Dictionary* d = new Dictionary();
	int choice = 0;
	while (choice != 11) {
		
		cout << endl;
		cout << "=====================================================" << endl;
		cout << "- ���� 2-3 ������" << endl;
		cout << "=====================================================" << endl;
		cout << " (1) �������� ����� � �������� � ������ �� �����" << endl;
		cout << " (2) �������� ��������� ����� � ��������" << endl;
		cout << " (3) �������� � ������ ���� � �������� � ����������" << endl;
		cout << " (4) ������� ������ � �������" << endl;
		cout << " (5) ��������� ������ � �����" << endl;
		cout << " (6) ������ �������� �� �����" << endl;
		cout << " (7) ������� ���� � ��������" << endl;
		cout << " (8) ������� ��� ������" << endl;
		cout << " (9) �������� ���-�� ���������� ������" << endl;
		cout << "(10) �������� ������ ������" << endl;
		cout << "(11) ����� " << endl;
	
		cout << "������� ��������: "; cin >> choice;
		
		// �������� �� �����
		if (choice == 1) {
			string FileName;
			cout << "������� �������� �����: "; cin >> FileName;
			ifstream ifs; // ������� ����
			ifs.open(FileName);

			unsigned int N;
			
			if (ifs.is_open()) {
				string nextString;
				while (ifs >> nextString)
				{
					if (ConvertStringToInt(nextString, N))
					{
						int success;
						unsigned int i;

						for (i = 0; i < N; i++)
						{
							try
							{
								Template* currentData = Template::Read(ifs);

								if (currentData != NULL)
								{
									success = d->Insert(currentData->GetKey(), currentData);

									if (!success)
									{
										delete currentData;
									}
								}
								else // ������ - ���������������� ����
								{
									cout << "�������� ������� ����!" << endl;

									ifs.close();
									d->FreeAllElements();
								}
							}
							catch (char* message)
							{
								cout << message << endl;
							}
						}
						break;
					}
					else
					{
						ifs.close();
						d->FreeAllElements();
					}
				}
				ifs.close();
			}
			else 
				cout << "�������� ��� �����." << endl;
			system("pause");
			system("cls");
		}
		// �������� ���������
		else if (choice == 2) {
			int num = 0;
			cout << "������� ���-�� ��������� ��� (���� � ��������): "; cin >> num;
			srand(time(NULL));
			for (int i = 0; i < num; i++) {
				string newk = generateRandomString();
				int newdata = rand() % 101;
				Template* currentData = Template::Readfromkeyboard(newk, newdata);
				int success;
				if (currentData != NULL)
				{
					success = d->Insert(currentData->GetKey(), currentData);

					if (!success)
					{
						delete currentData;
					}
					else {
						cout << i + 1 << " ���� ������� ���������!" << endl;
					}
				}
			}
			system("pause");
			system("cls");
		}
		// �������� � ����������
		else if (choice == 3) {
			string newk;
			cout << "������� ����: "; cin >> newk;
			int data;
			cout << "������� data: "; cin >> data;
			Template* currentData = Template::Readfromkeyboard(newk, data);
			int success;
			if (currentData != NULL)
			{
				success = d->Insert(currentData->GetKey(), currentData);

				if (!success)
				{
					delete currentData;
				}
				else {
					cout << "������� ���������!" << endl;
				}
			}
			system("pause");
			system("cls");
		}
		// ������� � �������
		else if (choice == 4) {
			d->PrintDictionaryConsole();
			system("pause");
			system("cls");
		}
		// ��������� ������ � �����
		else if (choice == 5) {
			string outputFile;
			cout << "������� �������� ������ �����: "; cin >> outputFile;

			ofstream ofs; // ���� ������
			ofs.open(outputFile);

			d->PrintDictionary(ofs);
			
			ofs.close();
			system("pause");
			system("cls");
		}
		// ������ �������� �� �����
		else if (choice == 6) {
			string k;
			cout << "������� ����: "; cin >> k;
			StringKey* sk = new StringKey(k);

			cout << "���� " << k << " �� ��������� " << *(d->Find(sk)) << endl;
			system("pause");
			system("cls");
		}
		// ������� ���� � ��������
		else if (choice == 7) {
			string kdel;
			cout << "������� ����, ������� ����� �������: "; cin >> kdel;

			StringKey* sk = new StringKey(kdel);

			Template* currentData = d->Delete(sk);

			if (d->Find(sk) == NULL)
				cout << "������� �������!" << endl;
			else
				cout << "�������� �� �������!" << endl;

			delete currentData; // �������� ���������
			delete sk; // ����������
			system("pause");
			system("cls");
		}
		// ������� ��� ������
		else if (choice == 8) {
			string flag;
			cout << "�� ������������� ������ ������� ��� ������ (Y/N): "; cin >> flag;
			if (flag == "Y") {
				d->FreeAllElements();
				if(d->IsEmpty())
					cout << "������ �������!" << endl;
				else
					cout << "������! ������ �� �������." << endl;
			}
			else
				cout << "�������� ��������!" << endl;

			system("pause");
			system("cls");
		}
		// �������� ���-�� ���������� ������
		else if (choice == 9) {
			int count_k = d->CountOfKey();
			if (count_k == 0)
				cout << "������ ������! ���������� ���������� ������: 0" << endl;
			else
				cout << "���������� ���������� ������: " << count_k << endl;
			system("pause");
			system("cls");
		}
		//�������� ������ ������
		else if (choice == 10) {
			int count_n = d->CountOfHeight();
			if (count_n == 0)
				cout << "������ ������! ������ ����� 0" << endl;
			else
				cout << "������ ������: " << count_n << endl;
			system("pause");
			system("cls");
		}
	}

	// ������� ������ �� ������
	d->FreeAllElements();
	delete d; // �������� �������

	return 0;
}

bool ConvertStringToInt(const string& s, unsigned int& num)
{
	istringstream myStream(s);

	if (myStream >> num)
		return true;
	else
		return false;
}

string generateRandomString()
{
	unsigned int outputLength = 10;
	string allowedChars = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	int randomIndex;
	string outputString = "";

	for (unsigned int i = 0; i < outputLength; ++i) {
		randomIndex = rand() % allowedChars.length();
		outputString += allowedChars[randomIndex];
	}

	if (outputString.empty()) {
		return generateRandomString();
	}
	else {
		return outputString;
	}
}