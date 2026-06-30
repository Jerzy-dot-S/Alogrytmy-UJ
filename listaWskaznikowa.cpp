#include <cstdio>

typedef int elementtype;
struct celltype {
elementtype element;
celltype * next;
};
typedef celltype * position;
class Lista
{

protected :
position l; // wskaźnik do głowy listy
public:
Lista() {
    l = new celltype; 
    l->next = nullptr;
}

~Lista() {
    position p = l;
    while (p != nullptr) {
        position tmp = p; 
        p = p->next;
        delete tmp;
    }
}

void Insert(elementtype x, position p) {
    position tmp = p -> next; //tmp do przeniesienia komórki dalej
    p -> next = new celltype; //Nowa komórka 
    p -> next -> next = tmp; //Komórka jest przenoszona
    p -> next -> element = x; //wstawiamy wartość dla nowej komórki
}

void Delete(position p) {
    celltype * tmp = p -> next; //Kopiuje wartość wskaźnika do tmp
    p -> next = p -> next -> next; //P jest wskaźnikiem na jeszcze następną komórke
    delete tmp; //Usuwam komórke 
}

elementtype Retrieve(position p) {
    if (p != nullptr && p->next != nullptr) { //Jak ten p istnieje i następny istnieje to
        return p->next->element; //Zwracam element z następnej komórki
    }
    return 0; //Jak błąd to 0
}

position Locate(elementtype x) {
    celltype * p = l; //Wskaźnik na header                 //kiedy następna komórka istnieje i jej element jest równy szukanemu x
    while (p -> next != nullptr && p -> next -> element != x) {  //i jej element jest równy szukanemu x
        p = p -> next; //idziemy po każdej komórce listy                    
    } return p; //Zwracamy pozycje komórki z elementem x
}

position First() {
    return l; //Zwracam głowe listy
}

position Next(position p) {
    return p -> next; //Zwracam następną komórke 
}

position Previous(position p) {
    celltype * tmp = l; //Wskaźnik na header
    while (tmp -> next != p) {  //Kiedy następna komórka nie równa sie p to
        tmp = tmp -> next; //Idziemy po wszystkich komórkach
    } return tmp;
}

position END() {
    celltype * p = l; //Wskaźnik na header
    while (p -> next != nullptr) { //Kiedy komórka za p istnieje to
        p = p -> next; //idziemy do następnej komórka
    } return p;
}
};

void print(Lista &l) //Funkcja to wypisywania 
{
    position i = l.First(); //Głowa listy
    while (i != nullptr && i->next != nullptr) //Kiedy i istnieje i komórka za i istnieje
    {
        printf(" %d,", l.Retrieve(i)); //Wypisujemy i
        i = l.Next(i); //Ustawiamy wskaźnik na następną komórke
    }
    printf("\n");
}

int main() {
    Lista list; //Obiekt
    position pierwszy = list.First(); //Wskaźnik na pierwszą pozycje 
    list.Insert(5, pierwszy); //Wstawiamy 5 na pierwszą pozycje 
    elementtype firstVal = list.Retrieve(pierwszy); //Kopia elementu pierwszego
    printf("Pierwszy element: %d\n", firstVal); //Wypisuje
    
    
    list.Insert(2, pierwszy); //2 na pierwszą pozycje
    elementtype firstVal2 = list.Retrieve(pierwszy); //Inna zmienna bo firstVal ma już wartość
    printf("Pierwszy element: %d\n", firstVal2); //Wypisuje
    position drugi = list.Next(pierwszy); //Wskaźnik na pozycje za pierwszą
    elementtype SecondVal = list.Retrieve(drugi); //Kopia drugiego elementu
    printf("Drugi element: %d\n", SecondVal); //Wypisuje

    list.Insert(1,drugi); //Wrzucam 1 na drugą pozycje
    print(list); //Wypisuje liste

    position end = list.END(); //Wskaźnik na koniec listy
    list.Insert(100,end); //100 na koniec listy
    print(list); //Wypisuje liste

    position sto = list.Locate(100); //Wskaźnik na komórke ze 100
    position przedsto = list.Previous(sto); //Wskaźnik na komórke przed 100
    list.Delete(przedsto); //Usuwam komórke przed 100
    print(list); //Wypisuje

    position jeden = list.Locate(1);
    position przedjedynka = list.Previous(jeden);
    list.Insert(5,przedjedynka);
    print(list);
}