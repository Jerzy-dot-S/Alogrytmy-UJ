#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

typedef int elementtype;

struct celltype {
	elementtype element;
	celltype *next;
};

typedef celltype *position;

class Queue {
protected:
	position front; // początek
	position rear;  // ostatni element

public:
	Queue();
	~Queue();

	void Enqueue(elementtype x);
	void Dequeue();
	elementtype FrontElem() const;
	bool Empty() const;
	void MakeNull();
};

Queue::Queue() { //Konstruktor
	front = new celltype;    
	front->next = nullptr;
	rear = front;
}

Queue::~Queue() { //destrukor
	MakeNull();
	delete front;
	front = nullptr;
	rear = nullptr;
}

bool Queue::Empty() const { //Sprawdza czy puste
	return front == rear; //Jeśli głowa to też tył kolejki to znaczy że jest tylko front
}

void Queue::Enqueue(elementtype x) {
	position p = new celltype;
	p->element = x; //Wskaźnik na element
	p->next = nullptr; //Ustawiamy że nic nie ma za tą komórką
	rear->next = p; //Zmiana wskaźnika z poprzedniego rear na p
	rear = p; //p to nowe rear
}

void Queue::Dequeue() {
	if (Empty()) {
		throw std::underflow_error("Queue is empty"); //Jak pusta to nie działa
	}
	position p = front->next; //Wskaźnik na usuwany element
	front->next = p->next;    // zmiana następnego elementu na front
	if (rear == p) {
		rear = front;         // jak tylko jeden element to rear = front
	}
	delete p; //Usuwamy pierwszy element
}

elementtype Queue::FrontElem() const {
	if (Empty()) {
		throw std::underflow_error("Queue is empty");
	}
	return front->next->element;
}

void Queue::MakeNull() {
	while (!Empty()) {
		Dequeue();
	}
}


int main() {
	Queue q;
	cout << std::boolalpha;

	cout << "Empty(): " << q.Empty() << endl;

	q.Enqueue(5);
	cout << "Enqueue(5)" << endl;
	cout << "Empty(): " << q.Empty() << endl;
	cout << "Front(): " << q.FrontElem() << endl;

	q.Dequeue();
	cout << "Dequeue()" << endl;
	cout << "Empty(): " << q.Empty() << endl;

	q.Enqueue(4);
	q.Enqueue(3);
	q.Enqueue(2);
	cout << "Enqueue(4), Enqueue(3), Enqueue(2)" << endl;
	cout << "Front(): " << q.FrontElem() << endl;

	q.Enqueue(1);
	cout << "Enqueue(1)" << endl;
	cout << "Front(): " << q.FrontElem() << endl;

	q.Dequeue();
	cout << "Dequeue()" << endl;
	cout << "Front(): " << q.FrontElem() << endl;

	q.Enqueue(6);
	cout << "Enqueue(6)" << endl;
	cout << "Front(): " << q.FrontElem() << endl;

	q.Dequeue();
	q.Dequeue();
	cout << "Dequeue(), Dequeue()" << endl;
	cout << "Front(): " << q.FrontElem() << endl;

	q.MakeNull();
	cout << "MakeNull()" << endl;
	cout << "Empty(): " << q.Empty() << endl;

	return 0;
}
