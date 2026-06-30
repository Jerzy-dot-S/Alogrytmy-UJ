#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

typedef int Telement; // teraz węzły przechowują pojedyncze znaki

struct Node { //Struktura z info i wskaźnikami
    Telement info;
    Node* left;
    Node* right;
};

typedef Node* PNode;

class BinaryTree {
protected:
    PNode T; // wskaźnik do korzenia
public:
    BinaryTree() { //Konstruktor
        T = nullptr;
    }

    ~BinaryTree() { //destruktor
        MAKENULL(T);
    }

    PNode PARENT1(PNode n, PNode t) { //Funkcja pomocznicza do rekurencyjnego przeszukiwania drzewa
        if (!t) return nullptr; //Jak nie istnieje to przerywamy 
        if (t->left == n || t->right == n) return t; //Jeśli prawe lub lewe dziecko to węzeł dla którego szukamy rodzica to zwracamy t
        PNode p = PARENT1(n, t->left); //Rekurencja
        if (p) return p;
        return PARENT1(n, t->right);
    }

    PNode PARENT(PNode n) { //Funckcja do znalezienia rodzica węzła
        if (!n || n == T) return nullptr; //Jeśli n nie istnieje lub n to korzeń 
        return PARENT1(n, T); //Uruchamiamy funkcje pomocniczą
    }

    PNode LEFT_CHILD(PNode n) {
        if (n) //Jeśli n istnieje to zwracamy left
            return n->left;
        else
            return nullptr;
    }

    PNode RIGHT_CHILD(PNode n) {
        if (n) //Jeśli n istnieje to zwracamy right
            return n->right;
        else
            return nullptr;
    }

    Telement GetLabel(PNode n) {
        if (n) //Jeśli n istnieje to zwracamy wartość w info
            return n->info;
        else
            return 0;
    }

    PNode BuildTree1(int m) { //Funkcja rekurencyjna do budowania drzewa
        if (m == 0) return nullptr;

        Telement x;
        std::cin >> x; // pobieramy kolejną wartość od użytkownika

        PNode root = new Node; //Tworzymy nowy node 
        root->info = x; //Wzkaźnik na wartość x 
        root->left = nullptr; //Dzieci jeszcze nie ma więc nullptr
        root->right = nullptr;

        int leftCount = m / 2; //Połowa węzłów na lewo
        int rightCount = m - (m / 2) - 1; //Reszta na prawo

        root->left = BuildTree1(leftCount); //Rekurencja 
        root->right = BuildTree1(rightCount);

        return root;
    }

    void BuildTree(int m) {
        T = BuildTree1(m); //Wywołuje BuildTree1 które zwraca korzeń i przypisuje do wskaźnik do T
    }

    PNode ROOT() { //Zwraca korzeń
        return T;
    }

    void MAKENULL(PNode p) {
        if (!p) return; //Jak nie ma node to przerywa
        MAKENULL(p->left); //Rekurencyjnie usuwa prawe i lewe dziecko
        MAKENULL(p->right);
        delete p; 
        if (p == T) T = nullptr; //Jeśli czyścimy całe drzewo to ustawia root na nullptr
    }

    void PreOrder(PNode t) {
        if (!t) return;
        std::cout << t->info << ' ';
        PreOrder(t->left); 
        PreOrder(t->right); 
    }

    void InOrder(PNode t) {
        if (!t) return;
        InOrder(t->left);
        std::cout << t->info << ' ';
        InOrder(t->right);
    }

    void PostOrder(PNode t) {
        if (!t) return;
        PostOrder(t->left);
        PostOrder(t->right);
        std::cout << t->info << ' ';
    }
};

int main() {
#ifdef _WIN32
    // Ustawienie kodowania UTF-8 w konsoli Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    BinaryTree bt;

    int m = 9;
    std::cout << "Podaj " << m << " wartości (np. a b c d e f g h i): ";
    bt.BuildTree(m);

    PNode r = bt.ROOT();
    if (!r) {
        std::cout << "\nDrzewo puste\n";
        return 0;
    }

    std::cout << "\nKorzeń: " << bt.GetLabel(r) << "\n";
    if (bt.LEFT_CHILD(r))
        std::cout << "Lewe dziecko korzenia: " << bt.GetLabel(bt.LEFT_CHILD(r)) << "\n";
    if (bt.RIGHT_CHILD(r))
        std::cout << "Prawe dziecko korzenia: " << bt.GetLabel(bt.RIGHT_CHILD(r)) << "\n";

    // Rodzic prawego dziecka korzenia
    if (bt.RIGHT_CHILD(r)) {
        PNode pr = bt.RIGHT_CHILD(r);
        PNode parent_pr = bt.PARENT(pr);
        if (parent_pr)
            std::cout << "Rodzic prawego dziecka korzenia: " << bt.GetLabel(parent_pr) << "\n";
    }

    // Rodzic prawego dziecka lewego dziecka korzenia
    if (bt.LEFT_CHILD(r) && bt.RIGHT_CHILD(bt.LEFT_CHILD(r))) {
        PNode plr = bt.RIGHT_CHILD(bt.LEFT_CHILD(r));
        PNode parent_plr = bt.PARENT(plr);
        if (parent_plr)
            std::cout << "Rodzic prawego dziecka lewego dziecka korzenia: " << bt.GetLabel(parent_plr) << "\n";
    }

    if (bt.PARENT(bt.LEFT_CHILD(bt.LEFT_CHILD(bt.RIGHT_CHILD(r)))))
        std::cout << "Test: " << bt.GetLabel(bt.PARENT(bt.LEFT_CHILD(bt.LEFT_CHILD(bt.RIGHT_CHILD(r))))) << "\n";

    // Wypisywanie w porządkach preorder, inorder, postorder
    std::cout << "Preorder: ";
    bt.PreOrder(r);
    std::cout << '\n';

    std::cout << "Inorder: ";
    bt.InOrder(r);
    std::cout << '\n';

    std::cout << "Postorder: ";
    bt.PostOrder(r);
    std::cout << '\n';

    return 0;
}
