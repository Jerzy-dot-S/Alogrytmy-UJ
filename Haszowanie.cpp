#include <iostream>
#include <cstring>
#ifdef _WIN32
#include <windows.h>
#endif

const int B = 65;              // Rozmiar tablicy
typedef char* elementtype;     // Klucz

struct celltype {
	elementtype element;
	celltype* next;
};

typedef celltype* position;

class dictionary {
protected:
	position D[B]; // tablica nagłówków list

public:
	dictionary();
	~dictionary();

	void Makenull();
	bool Member(elementtype x);
	void Insert(elementtype x);
	void Delete(elementtype x);
	int H(elementtype x);
};

dictionary::dictionary() { //Konstruktor. Przechodzi przez cała tablice i ustawia wszystkie wartośći na null
	for (int i = 0; i < B; ++i) {
		D[i] = nullptr; 
	}
}

dictionary::~dictionary() { //Destruktor
	Makenull();
}

void dictionary::Makenull() {
	for (int i = 0; i < B; ++i) { //Pętla po całej tablicy
		position p = D[i];
		while (p != nullptr) { //Przechodzimy po wszystkich p i usuwamy po kolei aż skonczą sie wskaźniki na następne
			position tmp = p; 
			p = p->next;
			delete tmp;
		}
		D[i] = nullptr; //Na końcu ustawia element tablicy na null
	}
}

int dictionary::H(elementtype x) {
	if (x == nullptr || x[0] == '\0') return 0; //Sprawdzamy czy x jest null lub jest końcem stringa
	unsigned char c = static_cast<unsigned char>(x[0]); //Rzutowanie na unsinged char żeby modulo było bez znaku
	return c % B; //Ustawiamy do której części tablicy ma trafić x
}

bool dictionary::Member(elementtype x) {
	int bucket = H(x); //Sprawdzamy w którym miejscu tablicy powinno być x
	position p = D[bucket];
	while (p != nullptr) { //Przechodzimy przez wszystkie elementy p z tego miejsca tablicy
		if (std::strcmp(p->element, x) == 0) //I sprawdzamy czy któryś z nich jest naszym x
			return true;
		p = p->next;
	}
	return false; //Jak nie należ to false
}

void dictionary::Insert(elementtype x) {
	if (Member(x)) return; // Jeśli jest już w słowniku

	int bucket = H(x);
	position p = new celltype;
	p->element = x;       // Element w p to x
	p->next = D[bucket];  // p->next ustawiamy jako wskaźnik wcześniej zapisany w D[bucket]
	D[bucket] = p; 		  // Ustawiamy element tej tablicy jako wskaźnik na p
}

void dictionary::Delete(elementtype x) {
	int bucket = H(x);
	position p = D[bucket];
	if (p == nullptr) return; // Jeśli lista pusta

	// Jeśli x jest na początku
	if (std::strcmp(p->element, x) == 0) {
		D[bucket] = p->next; //Ustawiamy D[bucket] jako wskaźnik na następne p
		delete p; //Usuwamy p
		return;
	}

	// Jeśli nie jest na początku
	position prev = p; // Poprzedni cell
	p = p->next;
	while (p != nullptr && std::strcmp(p->element, x) != 0) { //Przechodzimy przez wszystkie komórki w poszukiwaniu x
		prev = p;
		p = p->next;
	}
	if (p != nullptr) { // Jak znajdziemy x to ustawiamy porzednią komórke przed p na komórke po p
		prev->next = p->next;
		delete p;
	}
}

int main() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif

	dictionary dict;

	char ala[] = "Ala";
	char as[] = "As";
	char nazwisko[] = "Satora";

	// Wstaw Ala
	std::cout << "Insert: Ala" << std::endl;
	dict.Insert(ala);

	// Wypisz Member Ala
	std::cout << "Member(Ala): " << (dict.Member(ala) ? "true" : "false") << std::endl;

	// Wypisz wartość funkcji haszującej dla Ala
	std::cout << "H(Ala): " << dict.H(ala) << std::endl;

	// Wstaw As
	std::cout << "Insert: As" << std::endl;
	dict.Insert(as);

	// Wypisz Member As
	std::cout << "Member(As): " << (dict.Member(as) ? "true" : "false") << std::endl;

	// Wypisz wartość funkcji haszującej dla As
	std::cout << "H(As): " << dict.H(as) << std::endl;

	// Wypisz Member Ala 
	std::cout << "Member(Ala): " << (dict.Member(ala) ? "true" : "false") << std::endl;

	// Wypisz wartość funkcji haszującej dla Ala 
	std::cout << "H(Ala): " << dict.H(ala) << std::endl;

	// Wstaw swoje nazwisko
	std::cout << "Insert: " << nazwisko << std::endl;
	dict.Insert(nazwisko);

	// Wypisz wartość funkcji haszującej dla swojego nazwiska
	std::cout << "H(" << nazwisko << "): " << dict.H(nazwisko) << std::endl;

	// Wypisz Member dla swojego nazwiska
	std::cout << "Member(" << nazwisko << "): " << (dict.Member(nazwisko) ? "true" : "false") << std::endl;

	// Usuń Ala
	std::cout << "Delete: Ala" << std::endl;
	dict.Delete(ala);

	// Wypisz Member As
	std::cout << "Member(As): " << (dict.Member(as) ? "true" : "false") << std::endl;

	// Wypisz Member Ala
	std::cout << "Member(Ala): " << (dict.Member(ala) ? "true" : "false") << std::endl;

	// Makenull
	std::cout << "MAKENULL" << std::endl;
	dict.Makenull();

	// Wypisz Member As po MAKENULL
	std::cout << "Member(As): " << (dict.Member(as) ? "true" : "false") << std::endl;

	// Wypisz Member dla swojego nazwiska po MAKENULL
	std::cout << "Member(Satora): " << (dict.Member(nazwisko) ? "true" : "false") << std::endl;

	return 0;
}

