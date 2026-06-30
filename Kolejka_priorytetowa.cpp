#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

class Container 
{protected:
    
    Container (){};
 public:
    virtual unsigned int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
    virtual void MakeNull() = 0;
 };
 

template <typename T>
class PriorityQueue : public Container
{
public:
    virtual void Enqueue (T element) = 0;
    virtual T  FindMin () const = 0;
    virtual T DequeueMin () = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
protected:
    int count;
	std::vector<T> data;
    
public:
    
	BinaryHeap (unsigned int n);
	BinaryHeap ();
	~BinaryHeap (){;};
	void MakeNull();
	void Enqueue (T element);
	T FindMin () const;
	T DequeueMin ();
	bool IsEmpty () const;
    bool IsFull () const ;
    void Wypisz() const;
    unsigned int Count() const {return count;}
	
};

template <typename T>
BinaryHeap<T>::BinaryHeap (unsigned int n):count(0),data(n){};

template <typename T>
void BinaryHeap<T>::MakeNull() {
    count = 0;
}

template <typename T>
void BinaryHeap<T>::Enqueue(T element) {
    if (IsFull()) data.resize(data.size() == 0 ? 1 : data.size() * 2); //Jeśli wielkość to 0 to ustawia na jeden. Jeśli nie to podwaja

        int i = count;
        data[i] = element;
        count++;

        while (i > 0) { 
            int parent = (i - 1) / 2; //Lokalizacja rodzica
            if (data[parent] <= data[i]) { //Jeśli dziecko większe to przerywa
                break;
            }
            std::swap(data[parent], data[i]); //Jeśli nie to zamienia węzły 
            i = parent; //I ustawia element w miejscu parent
        }
}

template <typename T>
T BinaryHeap<T>::FindMin() const {
    if (IsEmpty()) throw std::underflow_error("Heap is empty"); //Jeśli puste to error 
    return data[0]; //Jak nie to zwraca pierwszy węzeł
}

template <typename T>
T BinaryHeap<T>::DequeueMin() { 
    if (IsEmpty()) throw std::underflow_error("Heap is empty"); //Jeśli puste to error

    T minValue = data[0]; //Wartość minimalna
    count--; //Od razu zmniejsza count

    if (count == 0) {
        return minValue; //Jeśli tylko 1 element to kończy
    }

    T lastValue = data[count]; //Ostatni element
    int i = 0;

    while (true) { //Pętla działa tak że przyjmujemy że na szzczycie jest największy element i po kolei sprawdzamy dzieci czy są większe aż do właściwego miejsca
        int left = 2 * i + 1; //Dzieci
        int right = 2 * i + 2;

        if (left >= count) { //Jeśli nie ma lewego dziecka to kończy pętlę bo nie ma gdzie dalej schodzić
            break; 
        }

        int smallerChild = left;
        if (right < count && data[right] < data[left]) { //Sprawdza czy prawe dziecko istnieje i czy jest mniejsze od lewego
            smallerChild = right;
        }

        if (data[smallerChild] >= lastValue) { //Jeśli dziecko jest większe to nie trzeba już spychać elementu
            break;
        }

        data[i] = data[smallerChild];
        i = smallerChild; //Zamiana węzłów kolejością
    }

    data[i] = lastValue; //Wstawia ostatni element w odpowiednie miejsce ustalone w pętli wyżej
    return minValue;

}

template <typename T>
bool BinaryHeap<T>::IsEmpty() const { //Sprawdza czy count jest 0
    return count == 0;
}

template <typename T>
bool BinaryHeap<T>::IsFull() const { //Sprawdza czy count jest większe od wielkości wektora
    return count >= data.size();
}

template <typename T>
void BinaryHeap<T>::Wypisz() const {
    if (IsEmpty()) {
        std::cout << "(empty)" << std::endl; //Jak puste to wypisuje
        return;
    }

    int index = 0;
    int nodesOnLevel = 1; //Przyjmuje początkowo że liczba węzłów na poziomie to 1

    while (index < count) { //Dopóki index mniejszy od tablicy
        int printed = 0;

        while (printed < nodesOnLevel && index < count) { //Dopóki nie wypisaliśmy wszystkich węzłów i index < count
            std::cout << data[index] << " "; //Wypisywanie
            ++index; //Zwiększamy ilość wypisanych
            ++printed;
        }

        std::cout << std::endl; //Następny poziom
        nodesOnLevel *= 2; //Zwiększamy dwukrotnie co poziom
    }
}

void WypiszMin(BinaryHeap<int>& q) {
    std::cout << "Min: " << q.FindMin() << std::endl;
}

void WykonajTest(unsigned int dlugoscWektora) {
    std::cout << "Test dla dlugosci wektora: " << dlugoscWektora << std::endl;

    BinaryHeap<int> q(dlugoscWektora);

    std::cout << "Czy pusta? " << (q.IsEmpty() ? "tak" : "nie") << std::endl;

    q.Enqueue(5);
    std::cout << "Po Enqueue(5):" << std::endl;
    std::cout << "Czy pusta? " << (q.IsEmpty() ? "tak" : "nie") << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.Enqueue(6);
    std::cout << "Po Enqueue(6):" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.Enqueue(8);
    std::cout << "Po Enqueue(8):" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.Enqueue(3);
    std::cout << "Po Enqueue(3):" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.Enqueue(9);
    std::cout << "Po Enqueue(9):" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.Enqueue(2);
    std::cout << "Po Enqueue(2):" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.Enqueue(1);
    std::cout << "Po Enqueue(1):" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.DequeueMin();
    std::cout << "Po DequeueMin():" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.DequeueMin();
    std::cout << "Po DequeueMin():" << std::endl;
    q.Wypisz();
    WypiszMin(q);

    q.MakeNull();
    std::cout << "Po MakeNull(), czy pusta? " << (q.IsEmpty() ? "tak" : "nie") << std::endl;
    std::cout << std::endl;
}

int main() {
    WykonajTest(10);
    WykonajTest(2);
    return 0;
}

