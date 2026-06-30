#include <iostream>

using std::cout;
using std::endl;

const int maxlength = 5;
typedef int elementtype;
typedef int position;

class Kolejka {
protected:
	elementtype Queue[maxlength];
	position Front; // indeks elementu z przodu kolejki
	position Rear;  // indeks ostatniego elementu

public:
	Kolejka();
	int AddOne(int i);
	void Enqueue(elementtype x);
	void Dequeue();
	elementtype FrontElem();
	void MakeNull();
	bool Empty();
};

Kolejka::Kolejka() { //Konstruktor kolejki. Ustawia Front na pierwszą komórkę
	Front = 0;		 // i rear na ostanią. maxlength -1 bo liczymy od 0
	Rear = maxlength - 1;
}

int Kolejka::AddOne(int i) {
	return (i + 1) % maxlength; //Dodaje 1 zgodnie z wielkością kolejki
}

bool Kolejka::Empty() {
	return AddOne(Rear) == Front; //Sprawdza czy jeśli dodamy jedną komórke do Rear to czy równa się Front
}

void Kolejka::MakeNull() { //Ustawia kolejkę na pustą
	Front = 0;
	Rear = maxlength - 1; 
}

void Kolejka::Enqueue(elementtype x) {
	if (AddOne(AddOne(Rear)) == Front) { //Sprawdzamy czy kolejka jest pełna dodając dwie komórki i sprawdzając czy równa się front
		cout << "Kolejka jest pelna" << endl;
		return;
	}
	Rear = AddOne(Rear); //Jak nie jest pełna to dodaje komórkę
	Queue[Rear] = x; //i dodaje tam element
}

elementtype Kolejka::FrontElem() {
	if (Empty()) {
		cout << "Kolejka jest pusta" << endl;
		return 0;
	}
	return Queue[Front]; //Zwraca wartość na początku
}

void Kolejka::Dequeue() {
	if (Empty()) {
		cout << "Kolejka jest pusta" << endl;
		return;
	}
	Front = AddOne(Front); //Zwiększa pole front o 1 usuwając początkowy element
}

int main() {
	Kolejka q;
	cout << std::boolalpha;

	/*cout << "Empty(): " << q.Empty() << endl;

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
	cout << "Empty(): " << q.Empty() << endl; */
	q.Enqueue(5); q.Enqueue(4); q.Enqueue(3); q.Enqueue(2); 
	cout << "Front:" << q.FrontElem() << endl;
	q.Enqueue(1);
	cout << "Front:" << q.FrontElem() << endl;
	q.Dequeue();
	cout << "Front:" << q.FrontElem() << endl;
	q.Enqueue(6);
	cout << "Front:" << q.FrontElem() << endl;

	q.Dequeue(); q.Dequeue(); q.Dequeue();
	cout << "Front:" << q.FrontElem() << endl;
	return 0;
}
