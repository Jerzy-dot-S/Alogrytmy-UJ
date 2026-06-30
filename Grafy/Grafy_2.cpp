#include <vector>
#include <string>
#include <iostream>
#include <windows.h>

template <typename T>
class Iterator
{
public:
virtual ~Iterator (){;}
Iterator(){;}
virtual bool IsDone () = 0;
virtual T & operator * () = 0;
virtual void operator ++ () = 0;
};

class Vertex
{
	int number;
public:
	int weight;
	std::string label;
	Vertex(int n);
	int Number() const;
};

class Edge
{
protected:
	Vertex* v0;
	Vertex* v1;
public:
	int weight;
	std::string label;
	Edge(Vertex *V0, Vertex* V1);
	Vertex* V0() { return v0; };
	Vertex* V1() { return v1; };
	Vertex* Mate(Vertex *v);
};

class GraphAsMatrix
{
 std::vector<Vertex *> vertices;
 std::vector< std::vector<Edge *> > adjacencyMatrix;
 bool isDirected;
 int numberOfVertices;
 int numberOfEdges=0;

 bool VertexExists(int v) const; //Dodatkowa metoda 

class AllVerticesIter: public Iterator<Vertex>
 {
 GraphAsMatrix & owner;
 int current;
 public:
 AllVerticesIter(GraphAsMatrix &owner);
 bool IsDone();
 Vertex & operator*();
 void operator++();
}; 
 class AllEdgesIter: public Iterator<Edge>
 {
 GraphAsMatrix & owner;
 int row;
 int col;
 public:
 void next();
 AllEdgesIter(GraphAsMatrix &owner);
 bool IsDone();
 Edge & operator*();
 void operator++(){next();}
 }; 
class EmanEdgesIter: public Iterator<Edge>
 {
 GraphAsMatrix & owner;
 int row;
 int col;
 public:
 void next();
 EmanEdgesIter(GraphAsMatrix &owner,int v);
 bool IsDone();
 Edge & operator*();
 void operator++(){next();}
};
class InciEdgesIter: public Iterator<Edge>
 {
 GraphAsMatrix & owner;
 int row;
 int col;
 public:
 void next();
 InciEdgesIter(GraphAsMatrix &owner,int v);
 bool IsDone();
 Edge & operator*();
 void operator++(){next();}
};
 public:
	GraphAsMatrix (int n, bool b);
	int NumberOfVertices();
	bool IsDirected();
	int NumberOfEdges();
	bool IsEdge(int u, int v);
	void MakeNull();
	void AddEdge (int u, int v);
	Edge * SelectEdge (int u, int v);
	Vertex * SelectVertex(int v);

	Iterator<Vertex> & VerticesIter();
	Iterator<Edge> & EdgesIter();
	Iterator<Edge> & EmanatingEdgesIter(int v);
	Iterator<Edge> & IncidentEdgesIter(int v);

}; 

GraphAsMatrix::AllVerticesIter::AllVerticesIter(GraphAsMatrix &owner) : owner(owner), current(0) { //Ustawia owner jako przekazane w argumencie i ustawia current na 0
}

bool GraphAsMatrix::AllVerticesIter::IsDone() { //Jeśli current większe bądź równe od liczby wierzchołków to skończył
	return current >= owner.NumberOfVertices();
}

Vertex & GraphAsMatrix::AllVerticesIter::operator*() { //Zwraca referencje do current Vertex
	return *owner.vertices[current];
}

void GraphAsMatrix::AllVerticesIter::operator++() { //Zwiększa current
	current++;
}

GraphAsMatrix::AllEdgesIter::AllEdgesIter(GraphAsMatrix &owner) : owner(owner) { //Ustawia pola i robi next
	row = 0;
	col = -1;
	next();
}

void GraphAsMatrix::AllEdgesIter::next() { //Ustawia current na następne pole macierzy sąsiedztw 
    int n = owner.NumberOfVertices();
    
    ++col; // Najpierw przesuwamy z bieżącej pozycji

    while (row < n) {
        while (col < n) {
            if (owner.adjacencyMatrix[row][col] != nullptr) {
                return;
            }
            ++col;
        }
        ++row;
        col = 0;
    }
}

bool GraphAsMatrix::AllEdgesIter::IsDone() { //Zwraca true jeśli row jest większe od ilości wierzchołków 
	return row >= owner.NumberOfVertices();
}

Edge & GraphAsMatrix::AllEdgesIter::operator*() { //Zwraca referencje do Edge 
	return *owner.adjacencyMatrix[row][col];
}

GraphAsMatrix::EmanEdgesIter::EmanEdgesIter(GraphAsMatrix &owner,int v) : owner(owner) { 
	if (owner.VertexExists(v)) { //Jeśli wierzchołek istnieje to ustawia rząd na ten wierzchołek 
		row = v;
		col = 0;
		next();
	} else { //Jak nie to ustawia na koniec
		row = owner.NumberOfVertices();
		col = owner.NumberOfVertices();
	}
}

bool GraphAsMatrix::EmanEdgesIter::IsDone() { //True jeśli na ostatniej kolumnie
	return col >= owner.NumberOfVertices();
}

void GraphAsMatrix::EmanEdgesIter::next() { //Ustawia na następną pole w rzędzie 
	int n = owner.NumberOfVertices();
	
	++col; // Najpierw przesuwamy z bieżącej pozycji

	while (col < n) { 
		if (owner.adjacencyMatrix[row][col] != nullptr) {
			return;
		}
		++col;
	}
}

Edge & GraphAsMatrix::EmanEdgesIter::operator*() { //Zwraca referencje na dany Edge
	return *owner.adjacencyMatrix[row][col];
}

GraphAsMatrix::InciEdgesIter::InciEdgesIter(GraphAsMatrix &owner,int v) : owner(owner) {
	if (owner.VertexExists(v)) { //Sprawdzamy czy v istnieje i dajemy na next 
		row = 0;
		col = v;
		next();
	} else { //Jak nie to na ostatni element macierzy sąsiedztw 
		row = owner.NumberOfVertices();
		col = owner.NumberOfVertices();
	}
}

void GraphAsMatrix::InciEdgesIter::next() { //Ustawia na następny element w kolumnie macierzy sąsiedztw 
	int n = owner.NumberOfVertices();
	
	++row; // Najpierw przesuwamy z bieżącej pozycji

	while (row < n) {
		if (owner.adjacencyMatrix[row][col] != nullptr) {
			return;
		}
		++row;
	}
}

bool GraphAsMatrix::InciEdgesIter::IsDone() { //Jak na końcu rzędu to true
	return row >= owner.NumberOfVertices();
}

Edge & GraphAsMatrix::InciEdgesIter::operator*() { //Zwraca referencje na dany edge 
	return *owner.adjacencyMatrix[row][col];
}

Iterator<Vertex> & GraphAsMatrix::VerticesIter() {//Metody tworzą iteratory
	return *(new AllVerticesIter(*this));
}

Iterator<Edge> & GraphAsMatrix::EdgesIter() {
	return *(new AllEdgesIter(*this));
}

Iterator<Edge> & GraphAsMatrix::EmanatingEdgesIter(int v) {
	return *(new EmanEdgesIter(*this, v));
}

Iterator<Edge> & GraphAsMatrix::IncidentEdgesIter(int v) {
	return *(new InciEdgesIter(*this, v));
}

Vertex::Vertex(int n) { //Konstruktor klasy Vertex
	number = n;
	weight = 0;
	label = "";
}

GraphAsMatrix::GraphAsMatrix(int n, bool b) {
    isDirected = b;                    // Ustawia czy graf skierowany
    numberOfVertices = n;              // Liczba wierzchołków
    numberOfEdges = 0;                 // Na start 0 krawędzi
    
    // Tworzy n wierzchołków
    for (int i = 0; i < n; i++) {
        vertices.push_back(new Vertex(i));
    }
    
    // Tworzy macierz n x n, wszystkie komórki to nullptr
    adjacencyMatrix.resize(n);         // n wierszy
    for (int i = 0; i < n; i++) {
        adjacencyMatrix[i].resize(n, nullptr);  // każdy wiersz ma n kolumn
    }
}

void GraphAsMatrix::AddEdge(int u, int v) {
	if (!VertexExists(u) || !VertexExists(v)) return; //Czy wierzchołki istnieją
	if (adjacencyMatrix[u][v]) return; //Czy ten edge już istnieje 

	Edge* e = new Edge(vertices[u], vertices[v]); //Wskaźnik na obiekt edge
	adjacencyMatrix[u][v] = e; //Ustawiamy w macierzy że jest przejście
	numberOfEdges++;

	if (isDirected == false) { //Jeśli nie jest skierowany to idzie w obie strony
		adjacencyMatrix[v][u] = e;
	}
	return;

}

bool GraphAsMatrix::IsEdge(int u, int v) { //Sprawdza czy jest krawędź między wierzchołakim
	if (!VertexExists(u) || !VertexExists(v)) return false; //Czy istnieją 
	if (adjacencyMatrix[u][v]) return true; //Jeśli jest w macierzy to true
	return false;
}

Edge* GraphAsMatrix::SelectEdge(int u, int v) {
	if (!IsEdge(u,v)) return nullptr; //Jak nie ma to nullptr
	return adjacencyMatrix[u][v]; //Jak jest to pointer na edge
}

int GraphAsMatrix::NumberOfVertices() {
	return numberOfVertices;
}

int GraphAsMatrix::NumberOfEdges() {
	return numberOfEdges;
}

bool GraphAsMatrix::IsDirected() {
	return isDirected;
}

void GraphAsMatrix::MakeNull() { //Ustawia wszystkie elementy macierzy na nullptr i numberofedges na 0
	for (int i = 0; i < (int)adjacencyMatrix.size(); i++) {
		for (int j = 0; j < (int)adjacencyMatrix[i].size(); j++) {
			adjacencyMatrix[i][j] = nullptr;
		}
	}
	numberOfEdges = 0;
}

Vertex* GraphAsMatrix::SelectVertex(int v) {
	if (!VertexExists(v)) return nullptr;
	return vertices[v]; //Jak istnieje to zwraca pointer na Vertex
}

bool GraphAsMatrix::VertexExists(int v) const { //Dodatkowa metoda żeby sprawdzić czy wierzchołek istnieje
	return v >= 0 && v < (int)vertices.size() && vertices[v] != nullptr; //Sprawdza czy v nie jest out of bounds i czy nie jest nullptr
}

int Vertex::Number() const {
	return number;
}

Edge::Edge(Vertex *V0, Vertex *V1) { //Zwraca połączone wierzchołki 
	v0 = V0;
	v1 = V1;
}

Vertex* Edge::Mate(Vertex* v) { //Zwraca sąsiadów
	if (v == v0) return v1;
	if (v == v1) return v0;
	return nullptr;
}



int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); //Polskie znaki

	GraphAsMatrix g(10, true);

	std::cout << "Liczba wierzcholkow: " << g.NumberOfVertices() << std::endl;
	std::cout << "Liczba krawedzi: " << g.NumberOfEdges() << std::endl;

	Vertex* v = g.SelectVertex(2);

	std::cout << "Numer v: " << v->Number() << std::endl;
	int unikalnyNumer = v->Number();
    v->weight = unikalnyNumer * unikalnyNumer;
	std::cout << "Waga v: " << v->weight << std::endl << std::endl;

	g.AddEdge(1,2);
	g.AddEdge(1,2);
	g.AddEdge(2,3);
	g.AddEdge(3,4);
	g.AddEdge(9,9);

	std::cout<< "Liczba wierzchołków: " << g.NumberOfEdges() << std::endl;
	std::cout<< "Liczba krawędzi: " << g.NumberOfVertices() << std::endl;
	std::cout<< "Czy istnieje (1,1): " << (g.IsEdge(1,1) ? "Tak" : "Nie") << std::endl;	
	std::cout<< "Czy istnieje (1,2): " << (g.IsEdge(1,2) ? "Tak" : "Nie") << std::endl;	
	std::cout<< "Czy istnieje (2,1): " << (g.IsEdge(2,1) ? "Tak" : "Nie") << std::endl << std::endl;	



	Edge* e = g.SelectEdge(1,2);

	std::cout << "Edge(1,2)" << std::endl;
	std::cout << "V0: " << e->V0()->Number() << std::endl;
	std::cout << "V1: " << e->V1()->Number() << std::endl;
	std::cout << "Sąsiad V0: " << e->Mate(e->V0())->Number() << std::endl;
	std::cout << "Sąsiad V1: " << e->Mate(e->V1())->Number() << std::endl;
	int weight = e->weight = e->V0()->Number() + e->V1()->Number();
	std::cout << "Waga krawędzi (1,2): " << weight << std::endl << std::endl;



	e = g.SelectEdge(2,3);

	std::cout << "Edge(2,3)" << std::endl;
	std::cout << "V0: " << e->V0()->Number() << std::endl;
	std::cout << "V1: " << e->V1()->Number() << std::endl;
	std::cout << "Sąsiad V0: " << e->Mate(e->V0())->Number() << std::endl;
	std::cout << "Sąsiad V1: " << e->Mate(e->V1())->Number() << std::endl;
	weight = e->weight = e->V0()->Number() + e->V1()->Number();
	std::cout << "Waga krawędzi (2,3): " << weight << std::endl << std::endl;



	e = g.SelectEdge(3,4);

	std::cout << "Edge(3,4)" << std::endl;
	std::cout << "V0: " << e->V0()->Number() << std::endl;
	std::cout << "V1: " << e->V1()->Number() << std::endl;
	std::cout << "Sąsiad V0: " << e->Mate(e->V0())->Number() << std::endl;
	std::cout << "Sąsiad V1: " << e->Mate(e->V1())->Number() << std::endl;
	weight = e->weight = e->V0()->Number() + e->V1()->Number();
	std::cout << "Waga krawędzi (3,4): " << weight << std::endl << std::endl;



	e = g.SelectEdge(9,9);

	std::cout << "Edge(9,9)" << std::endl;
	std::cout << "V0: " << e->V0()->Number() << std::endl;
	std::cout << "V1: " << e->V1()->Number() << std::endl;
	std::cout << "Sąsiad V0: " << e->Mate(e->V0())->Number() << std::endl;
	std::cout << "Sąsiad V1: " << e->Mate(e->V1())->Number() << std::endl;
	weight = e->weight = e->V0()->Number() + e->V1()->Number();
	std::cout << "Waga krawędzi (9,9): " << weight << std::endl << std::endl;



	std::cout << "Wszystkie wierzchołki" << std::endl;
	Iterator<Vertex>& vertIter = g.VerticesIter();
	while (!vertIter.IsDone()) {
		Vertex& currentVertex = *vertIter;
		std::cout << "Wierzchołek: " << currentVertex.Number() << " - Waga: " << currentVertex.weight << std::endl;
		++vertIter;
	}
	delete &vertIter; 
	std::cout << std::endl;


	g.AddEdge(3, 5);
	g.AddEdge(8, 3);
	g.AddEdge(5, 2);


	std::cout << "Wszystkie krawędzie" << std::endl;
	Iterator<Edge>& edgesIter = g.EdgesIter();
	while (!edgesIter.IsDone()) {
		Edge& currentEdge = *edgesIter;
		std::cout << "Krawędź: V0=" << currentEdge.V0()->Number() << " V1=" << currentEdge.V1()->Number() << std::endl;
		++edgesIter;
	}
	delete &edgesIter; 
	std::cout << std::endl;



	std::cout << "Krawędzie wychodzące z wierzchołka 3" << std::endl;
	Iterator<Edge>& emanIter = g.EmanatingEdgesIter(3);
	while (!emanIter.IsDone()) {
		Edge& currentEdge = *emanIter;
		std::cout << "Krawędź: V0=" << currentEdge.V0()->Number() << " V1=" << currentEdge.V1()->Number() << std::endl;
		++emanIter;
	}
	delete &emanIter; 
	std::cout << std::endl;



	std::cout << "Krawędzie dochodzące do wierzchołka 2" << std::endl;
	Iterator<Edge>& inciIter = g.IncidentEdgesIter(2);
	while (!inciIter.IsDone()) {
		Edge& currentEdge = *inciIter;
		std::cout << "Krawędź: V0=" << currentEdge.V0()->Number() << " V1=" << currentEdge.V1()->Number() << std::endl;
		++inciIter;
	}
	delete &inciIter; 
	std::cout << std::endl;

	return 0;
}