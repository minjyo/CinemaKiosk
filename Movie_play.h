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
	void valid(int count); //예외처리를 하기 위한 함수 (사용자 함수 X)
	int count;	//리스트의 크기를 저장할 변수
	Node* Head = new Node; // Head 노드
	int people = 0;
	int num;
	int p[25] = { 0, };
public:
	Movie_play(); 
	//Movie_play(unsigned short stime, Movie_info* minfo);//생성자
	/*
		Movie_play 함수 목록
	*/
	int get(int index);	//해당 index 데이터 출력
	void add(int Data); //맨 앞에 새로운 노드 추가 
	void add(int count, int Data); //해당 index에 새로운 노드 추가
	int size();	// List의 길이를 리턴함
	void set(int Index, int Data);	//데이터 값 변경
	void remove(int Index); //해당 index 삭제
	bool isEmpty();	//객체가 비어있는지 확인
	void chooseSeat();
	void printSeat();
	unsigned short start_time;
	unsigned short end_time;
};