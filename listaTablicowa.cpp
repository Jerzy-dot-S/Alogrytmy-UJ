#include <cstdio>

typedef int elementtype, position ;
const int maxlength=10;
struct List
{
	elementtype elements[maxlength];
	int last;           
};

position END(List l) {
	return l.last + 1; 
}

position First(List l) {
    if (l.last == -1) {
        return END(l); 
    } return 0; 
}

position Next(position p,List l){
    if (p < -1 || p >= END(l)) {
        return -1; 
    }

    if (p == l.last) {
        return END(l); 
    }
    return p+1; 
}


position Previous(position p,List l) {
    if (p == END(l)) {
        if (l.last == -1) return -1;
        return l.last;
    }

    if (p < 1 || p > l.last +1) {
        return -1;
    }

    if (p == First(l)) {
        return -1;
    }
    return p-1;
}



position Locate(elementtype x, List l) { 
    for (int i = 0; i <= l.last; ++i) {
        if (l.elements[i] == x) 
        return i;
    }
    return END(l);
}

elementtype Retrieve(position p, List l) {
    if (p >= 0 && p <= l.last) {
    return l.elements[p];
    } 
    return -10000000;
}

bool Insert(int x, position p, List &l) {
    if (l.last >= maxlength - 1) {
        return false;
    }

    if (p > l.last + 1 || p < 0) {
        return false;
    }

    for (int i = l.last; i >= p; i--) {
        l.elements[i + 1] = l.elements[i];
    }

    l.elements[p] = x;

    l.last++;
    return true;
}

bool Delete(position p, List &l) {
    if (p > l.last + 1 || p < 0) {
        return false;
    }

    for (int i = p; i < l.last; ++i) {
        l.elements[i] = l.elements[i + 1];
    }

    l.last--;
    return true;

}

void print(List l)
{
    position i = First(l);
    while (i != END(l))
    {
        printf(" %d,", Retrieve(i, l));
        i = Next(i, l);
    }
    printf("\n");
}

int main()
{
    List l;
    l.last = -1;

    Insert(100, First(l), l);
    print(l);                // powinno wypisać: 100

    for (int i = 0; i < 3; ++i) Insert(i, First(l), l);
    print(l);                // po wstawianiu na początek: 2,1,0,100

    Insert(20, Previous(END(l), l), l);
    print(l);                // wstaw w przedostatnie miejsce: 2,1,0,20,100

    Delete(Locate(20, l), l);
    print(l);                // po usunięciu 20: 2,1,0,100

    Delete(Locate(0,l),l);
    print(l);

    return 0;
}