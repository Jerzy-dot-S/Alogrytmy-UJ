#include <cstdio>
#include <climits>

typedef int elementtype;
typedef int position;
const int maxlength = 100;

class Stos {
    elementtype S[maxlength];
    position Top; // indeks szczytu
public:
    Stos() { Top = -1; } //konstruktor ustawia liste na pustą

    void Push(elementtype x) {
        if (Top >= maxlength - 1) { //Sprawdzamy czy jest miejsce w tablicy
            printf("Push failed: stack overflow\n"); //Jak pełny to komunikat
            return;
        }
        S[++Top] = x; //Jak nie jest pełny to element wyżej równa sie x
    }
    void Pop() {
        if (Top < 0) {
            printf("Pop: stack is empty\n");
            return;
        }
        --Top; //Usuwamy wartość
    }
    bool Empty() const {
        return Top == -1; //Jeśli top -1 to true
    }
    elementtype TopElem() const {
        if (Top < 0) {
            printf("TopElem: stack is empty\n");
            return INT_MIN; // Zwaracamy INT_MIN bo raczej nie będzie tej wartości w stosie
        }
        return S[Top]; 
    }
    void Makenull() {
        Top = -1;
    }
};

int main() {
    Stos st;

    // 1. Empty()
    printf("Empty(): %s\n", st.Empty() ? "true" : "false");

    // 2. Push(5)
    st.Push(5);
    printf("Push(5)\n");

    // 3. Top_Elem()
    elementtype v = st.TopElem();
    if (v != INT_MIN) printf("Top_Elem(): %d\n", v);

    // 4. Empty()
    printf("Empty(): %s\n", st.Empty() ? "true" : "false");

    // 5. Pop()
    st.Pop();
    printf("Pop()\n");

    // 6. Empty()
    printf("Empty(): %s\n", st.Empty() ? "true" : "false");

    // 7. Push(2)
    st.Push(2);
    printf("Push(2)\n");

    // 8. Push(3)
    st.Push(3);
    printf("Push(3)\n");

    // 9. TopElem()
    v = st.TopElem();
    if (v != INT_MIN) printf("TopElem(): %d\n", v);

    // 10. Makenull()
    st.Makenull();
    printf("Makenull()\n");

    // 11. Empty()
    printf("Empty(): %s\n", st.Empty() ? "true" : "false");

    return 0;
}
