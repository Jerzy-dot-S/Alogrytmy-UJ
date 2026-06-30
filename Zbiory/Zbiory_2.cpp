#include <vector>
#include <iostream>
#include <stdexcept>
 
template <typename T>
class Visitor
{
public:
    virtual void Visit (T & element) =0;
    virtual bool IsDone () const
	{ return false; }
};

template <typename T>
class Container 
{protected:
    
    Container (){};
 public:
    virtual int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
   	virtual void MakeNull() = 0;
 	virtual void Accept (Visitor<T> & v)=0; 
 };
 


template <typename T>
class Set : public virtual Container<T>
{
protected:
  int count;
  int universeSize;
public:
 Set (int n) : universeSize (n) {}
 int UniverseSize() const {return universeSize;}
 int Count() const {return count;};
 virtual void Insert (T element)=0;
 virtual bool IsMember (T element) const=0;
 virtual void Withdraw (T element)=0;
 };


class SetAsArray : public Set<int>
{
    std::vector<bool> array;
public:
    SetAsArray (unsigned int);
	void MakeNull();//metody z containera
    void Insert (int element);
	bool IsMember (int element) const;
	void Withdraw (int element);
	bool IsFull () const {return (Count()==UniverseSize());};
	void Accept (Visitor<int> & v) ;
	//friend- funkcja uzyska prawo dostepu do prywatnych element�w danej klasy.

	friend SetAsArray operator + (
	SetAsArray const&, SetAsArray const&);
	friend SetAsArray operator - (
	SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator * (
	SetAsArray const&, SetAsArray const&);
    friend bool operator == (
	SetAsArray const&, SetAsArray const&);
    friend bool operator <= (
	SetAsArray const&, SetAsArray const&);
    
    void Wypisz() const;	
};

class AddingVisitor : public Visitor<int> { //Dzieciczy po visitor
    int sum = 0;
public:
    void Visit(int& i) override {
        sum += i; //Jeśli odwiedzi komórke to dodaje do sumy
    }

    int GetSum() const {
        return sum; //Zwraca policzoną sumę
    }
};


class Odd_Visitor:public Visitor<int>
{
protected:
    bool IsDone_;
public:
    Odd_Visitor():IsDone_(false){}; //Inicjalizuje IsDone na false
    void Visit(int & element) { //Sprawdza czy przekazany element jest nieparzysty. Jak tak to zwraca true
        if (element%2==1) IsDone_=true;
};
    bool IsDone() const override {return IsDone_;} //Zwraca pole IsDone_
}; 

SetAsArray::SetAsArray(unsigned int N) : Set(N), array(N, false) { 
    count = 0;
}

void SetAsArray::Accept(Visitor<int> & v) { //Klasa która pozwala robić visitorom operacje ma elementach
    int end = -1;
    for (int i = 0; i < array.size(); i++) {
        if (array[i]) { //Jeśli element jest true to Visitor przeprowadza jakąś operacje
            v.Visit(i);
            if (v.IsDone()) { //Jeśli Visitor już skończył to przerwane
                end = i;
                break;
            }
        }
    }
    if (end != -1) {
        std::cout << "Accept skonczyła na: " << end << std::endl;
    } else { //Jeśli Visitor przeszedł całą pętlę to break nie jest używane więc pozostaje domyślan wartość end
        std::cout << "Accept przeszła caly zbiór." << std::endl;
    }
}

void SetAsArray::MakeNull() {
    for (int i = 0; i < array.size(); i++) { //Ustawia cały array na false i count na 0
        array[i] = false; 
    }
    count = 0;
}

void SetAsArray::Insert (int element) { //Podany element array ustawiany na true i count zwiększany
    if (array[element] == true) return;
    array[element] = true;
    count++;
}

bool SetAsArray::IsMember (int element) const { //Sprawdzamy czy podany element array jest true czy false
    if (array[element] == true) return true;
    return false;
}

void SetAsArray::Withdraw(int element) { //Ustawia dany element na false
    if (array[element] == true) array[element] = false;
}

SetAsArray operator+ (SetAsArray const& s, SetAsArray const& t) { 
    if (s.UniverseSize() != t.UniverseSize()) throw std::invalid_argument("Universe sizes do not match"); //Jak nie tej samej wielkości to error
    
    int i = 0;
    SetAsArray result(s.UniverseSize());
    while (i < s.UniverseSize()) { //Idziemy po każdym elemencie i sprawdzamy czy któryś jest true
        if (s.array[i] == true || t.array[i] == true) {
            result.Insert(i);
        }
        i++;
    }
    return result;
}

SetAsArray operator* (SetAsArray const& s, SetAsArray const& t) {
    if (s.UniverseSize() != t.UniverseSize()) throw std::invalid_argument("Universe sizes do not match");
    
    int i = 0;
    SetAsArray result(s.UniverseSize());
    while (i < s.UniverseSize()) {
        if (s.array[i] == true && t.array[i] == true) { //Sprawdzamy czy oba są true
            result.Insert(i);
        }
        i++;
    }
    return result;
}

SetAsArray operator- (SetAsArray const& s, SetAsArray const& t) {
    if (s.UniverseSize() != t.UniverseSize()) throw std::invalid_argument("Universe sizes do not match");
    
    int i = 0;
    SetAsArray result(s.UniverseSize());
    while (i < s.UniverseSize()) {
        if (s.array[i] == true && t.array[i] == false) { //Sprawdzamy czy jeden jest true i drugi false
            result.Insert(i);
        }
        i++;
    }
    return result;
}

bool operator== (SetAsArray const& s, SetAsArray const& t) {
    if (s.UniverseSize() != t.UniverseSize()) return false; //Jak innych rozmiarów to nei są równe

    for (int i = 0; i < s.UniverseSize(); i++) {
        if (s.array[i] != t.array[i]) return false; //Sprawdzamy czy którykolwiek element nie jest równy drugiemu
    }
    return true;
}

bool operator<= (SetAsArray const& s, SetAsArray const& t) {
    int i = 0;
    while (i < s.UniverseSize()) {
        if (s.array[i] == true && t.array[i] == false) return false; //Jeśli element jest s ale nie ma go w t to nie jest podzbiorem. 
        i++;
    }
    return true;
}

void SetAsArray::Wypisz() const { //Funkcja do wypisywania
    for(int i = 0; i < array.size(); i++) {
        if (array[i] == true) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

void parzyste(SetAsArray& A) { //Funkcja do ustawiania zbioru na tylko parzyste
    for(int i = 0; i < A.UniverseSize(); i += 2) {
        A.Insert(i);
    } 
}

void nieparzyste(SetAsArray& B) { //Funkcja do ustawiania zbioru na tylko nieparzyste
    for(int i = 1; i < B.UniverseSize(); i += 2) {
        B.Insert(i);
    }
}

int main () {
    SetAsArray A(10); SetAsArray B(10); SetAsArray C(10); SetAsArray D(10); SetAsArray E(10);
    
    parzyste(A);
    nieparzyste(B);

    C = A + B;
    D = C - B;

    std::cout << "A: "; A.Wypisz();
    std::cout << "B: "; B.Wypisz();
    std::cout << "C: "; C.Wypisz();
    std::cout << "D: "; D.Wypisz();
    std::cout << std::endl;

    std::cout << "D==A" << (D==A ? " Tak" : " Nie") << std::endl;
    std::cout << "D<=A" << (D<=A ? " Tak" : " Nie") << std::endl;
    std::cout << "C==B" << (C==B ? " Tak" : " Nie") << std::endl;
    std::cout << "B<=C" << (B<=C ? " Tak" : " Nie") << std::endl;

    A.Insert(1);
    std::cout << std::endl;   
    std::cout << "Po A.Insert(1)" << std::endl;
    std::cout << std::endl;

    std::cout << "D==A" << (D==A ? " Tak" : " Nie") << std::endl;
    std::cout << "D<=A" << (D<=A ? " Tak" : " Nie") << std::endl;

    std::cout << std::endl;

    A.Insert(5);
    AddingVisitor v_A;
    A.Accept(v_A);
    std::cout << "Suma elementów A po Insert(1): " << v_A.GetSum() << std::endl;
    std::cout << std::endl;

    E=A *B;
    AddingVisitor v_E;
    E.Accept(v_E);
    std::cout << "Suma elementów E: " << v_E.GetSum() << std::endl;
    std::cout << std::endl;

    E.Withdraw(1);
    AddingVisitor v_E_after;
    E.Accept(v_E_after);
    std::cout << "Suma elementów E po Withdraw(1): " << v_E_after.GetSum() << std::endl;
    std::cout << std::endl;

    Odd_Visitor ov_B;
    B.Accept(ov_B);
    std::cout << "Czy w B jest liczba nieparzysta: " << (ov_B.IsDone() ? " Tak" : " Nie") << std::endl;
    std::cout << std::endl;

    Odd_Visitor ov_A;
    A.Accept(ov_A);
    std::cout << "Czy w A jest liczba nieparzysta: " << (ov_A.IsDone() ? " Tak" : " Nie") << std::endl;
    std::cout << std::endl;

    A.Withdraw(1); //A.Withdraw(5);
    Odd_Visitor ov_A_after;
    A.Accept(ov_A_after);
    std::cout << "Czy w A jest liczba nieparzysta po Withdraw(1) i (5): " << (ov_A_after.IsDone() ? " Tak" : " Nie") << std::endl;
    std::cout << std::endl;

}
