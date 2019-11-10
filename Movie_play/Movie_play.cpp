#include <iostream>
#include "Movie_play.h"

using namespace std;

Movie_play::Movie_play()
{
	Head->nextNode = NULL;
	Movie_play::count = 0;
}

//Movie_play::Movie_play(unsigned short stime, Movie_info* minfo) {
//
//	this->end_time = stime + minfo.get_runnging_time();
//
//	/* ���� ���� 60���� ������ */
//	if (((stime % 100) + (minfo.get_running_time() % 100)) > 60) {
//		/* 60�� ���� 1�ð� ���ϴϱ� 40�� ���� */
//		this->end_time += 40;
//	}
//
//	Head->nextNode = NULL;
//	Movie_play::count = 0;
//}

int Movie_play::get(int index)
{
	try
	{
		valid(index);
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return -1;
	}

	Node* temp = Head;
	for (int i = 0; i <= index; i++) {
		temp = temp->nextNode;
	}
	return temp->data;
}

void Movie_play::valid(int count)
{
	if (count > Movie_play::count)
	{
		throw "Error : ��ȿ���� ���� index �Դϴ�.";
	}
}

int Movie_play::size()
{
	return Movie_play::count;
}

void Movie_play::add(int Data)
{
	Node* NewNode = new Node;
	NewNode->data = Data;
	NewNode->nextNode = NULL;

	if (Head->nextNode == NULL)
	{
		Head->nextNode = NewNode;
	}
	else
	{
		Node* temp = Head;
		while (temp->nextNode != NULL)
		{
			temp = temp->nextNode;
		}
		temp->nextNode = NewNode;
	}

	Movie_play::count++;
}

void Movie_play::add(int index, int Data)
{
	try
	{
		valid(index);
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}

	Node* NewNode = new Node;
	NewNode->data = Data;
	NewNode->nextNode = NULL;

	if (Head->nextNode == NULL)
	{
		Head->nextNode = NewNode;
	}
	else
	{
		Node* temp = Head;
		for (int i = 0; i < count; i++)
		{
			temp = temp->nextNode;
		}
		NewNode->nextNode = temp->nextNode;
		temp->nextNode = NewNode;
	}

	Movie_play::count++;
}

void Movie_play::set(int index, int Data)
{
	try
	{
		valid(index);
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}

	Node* temp = Head;
	for (int i = 0; i <= index; i++)
	{
		temp = temp->nextNode;
	}

	temp->data = Data;
}

void Movie_play::remove(int index)
{
	try
	{
		valid(index);
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		return;
	}

	Node* temp = Head;
	Node* remove = Head;

	for (int i = 0; i < index; i++)
	{
		temp = temp->nextNode;
		remove = remove->nextNode;
	}
	remove = remove->nextNode;

	temp->nextNode = remove->nextNode;
	remove->nextNode = NULL;
	delete remove;
	Movie_play::count--;
}

bool Movie_play::isEmpty()
{
	Node* head = Head;
	if (head->nextNode == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*=====================�Ʒ��� ��ȭ�� �޼ҵ�=====================*/

void Movie_play::chooseSeat() {
	int x, y, ok, a, b;
	cout << "�ο� �� �Է� : ";
	cin >> num;
	people += num;

	for (int i = 0; i < num;) {
		for (int k = 0; k < people; k++) {
			a = p[k] % 10;
			b = p[k] / 10 % 10;
			seat[a - 1][b - 1] = true;
		}
		cout << i + 1 << "��° �¼� �Է� (x, y): ";
		cin >> x >> y;
		if (x > 5 || y > 5) {
			cout << "��ȿ���� ���� �Է��Դϴ�. �ٽ� �Է����ּ���!" << endl;
		}
		else {
			if (seat[x - 1][y - 1] == false) {
				cout << "(" << x << "," << y << ") �� �����ϼ̽��ϴ�." << endl;
				seat[x - 1][y - 1] = true;
				printSeat();
				p[people - num + i] = y * 10 + x;
				i++;
			}
			else {
				cout << "�¼��� á���ϴ�.\n�ٸ� �¼��� �������ּ���." << endl;
			}
		}
	}
	do {
		cout << "����? (Y:1/N:0) : ";
		cin >> ok;

		if (ok == 1) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					seat[i][j] = false;
				}
			}

			for (int i = people - num; i < people; i++) {
				p[i] = 0;
			}
			for (int i = 0; i < people - num; i++) {

				a = p[i] % 10;
				b = p[i] / 10 % 10;

				seat[a - 1][b - 1] = true;
			}
			people -= num;
			chooseSeat();
		}
		else if (ok == 0) {
			cout << "�ѤѤѤѤѤѤѤѤѤ�Ȯ�ΤѤѤѤѤѤѤѤѤѤѤ�" << endl;
			printSeat();
		}
		else {
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;

		}
	} while (ok != 1 && ok != 0);
}

void Movie_play::printSeat() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (seat[i][j] == 0)
				cout << "��";
			else
				cout << "��";
		}
		cout << endl;
	}
}
