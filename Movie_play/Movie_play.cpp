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
//	/* 분의 합이 60분이 넘으면 */
//	if (((stime % 100) + (minfo.get_running_time() % 100)) > 60) {
//		/* 60분 빼고 1시간 더하니까 40을 더함 */
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
		throw "Error : 유효하지 않은 index 입니다.";
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

/*=====================아래는 영화관 메소드=====================*/

void Movie_play::chooseSeat() {
	int x, y, ok, a, b;
	cout << "인원 수 입력 : ";
	cin >> num;
	people += num;

	for (int i = 0; i < num;) {
		for (int k = 0; k < people; k++) {
			a = p[k] % 10;
			b = p[k] / 10 % 10;
			seat[a - 1][b - 1] = true;
		}
		cout << i + 1 << "번째 좌석 입력 (x, y): ";
		cin >> x >> y;
		if (x > 5 || y > 5) {
			cout << "유효하지 않은 입력입니다. 다시 입력해주세요!" << endl;
		}
		else {
			if (seat[x - 1][y - 1] == false) {
				cout << "(" << x << "," << y << ") 을 선택하셨습니다." << endl;
				seat[x - 1][y - 1] = true;
				printSeat();
				p[people - num + i] = y * 10 + x;
				i++;
			}
			else {
				cout << "좌석이 찼습니다.\n다른 좌석을 선택해주세요." << endl;
			}
		}
	}
	do {
		cout << "수정? (Y:1/N:0) : ";
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
			cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ확인ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
			printSeat();
		}
		else {
			cout << "잘못 입력하셨습니다." << endl;

		}
	} while (ok != 1 && ok != 0);
}

void Movie_play::printSeat() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (seat[i][j] == 0)
				cout << "□";
			else
				cout << "■";
		}
		cout << endl;
	}
}
