#pragma once
#define SIZE_COLUMN 5
#define SIZE_ROW 5

class Movie_play
{
private:
	class Node
	{
	public:
		int data;
		Node* nextNode;
	};
	bool seat[SIZE_COLUMN][SIZE_ROW] = { false, };
	void valid(int count); //����ó���� �ϱ� ���� �Լ� (����� �Լ� X)
	int count;	//����Ʈ�� ũ�⸦ ������ ����
	Node* Head = new Node; // Head ���
	int people = 0;
	int num;
	int p[25] = { 0, };
public:
	Movie_play(); 
	//Movie_play(unsigned short stime, Movie_info* minfo);//������
	/*
		Movie_play �Լ� ���
	*/
	int get(int index);	//�ش� index ������ ���
	void add(int Data); //�� �տ� ���ο� ��� �߰� 
	void add(int count, int Data); //�ش� index�� ���ο� ��� �߰�
	int size();	// List�� ���̸� ������
	void set(int Index, int Data);	//������ �� ����
	void remove(int Index); //�ش� index ����
	bool isEmpty();	//��ü�� ����ִ��� Ȯ��
	void chooseSeat();
	void printSeat();
	unsigned short start_time;
	unsigned short end_time;
};