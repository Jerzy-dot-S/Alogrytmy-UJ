#pragma once

#include <cstdio>
#include <climits>
#include <string>

typedef int elementtype;
typedef int position;
const int maxlength = 100;

// Stos tablicowy dla liczb calkowitych
class Stos {
    elementtype S[maxlength];
    position Top; // indeks szczytu
public:
    Stos() { Top = -1; } // konstruktor ustawia stos na pusty

    void Push(elementtype x) {
        if (Top >= maxlength - 1) { // sprawdzamy, czy jest miejsce w tablicy
            printf("Push failed: stack overflow\n");
            return;
        }
        S[++Top] = x; // odkladamy element na szczyt
    }

    void Pop() {
        if (Top < 0) {
            printf("Pop: stack is empty\n");
            return;
        }
        --Top; // "usuwamy" element ze szczytu
    }

    bool Empty() const {
        return Top == -1; // stos pusty, gdy Top == -1
    }

    elementtype TopElem() const {
        if (Top < 0) {
            printf("TopElem: stack is empty\n");
            return INT_MIN; // wartosc specjalna oznaczajaca blad
        }
        return S[Top];
    }

    int Size() const {
        return Top + 1; // liczba elementow na stosie
    }

    void Makenull() {
        Top = -1;
    }
};

// Stos tablicowy dla stringow
class StosString {
    std::string S[maxlength];
    position Top;
public:
    StosString() { Top = -1; }

    void Push(const std::string &x) {
        if (Top >= maxlength - 1) {
            printf("Push failed: stack overflow (string)\n");
            return;
        }
        S[++Top] = x;
    }

    void Pop() {
        if (Top < 0) {
            printf("Pop: stack is empty (string)\n");
            return;
        }
        --Top;
    }

    bool Empty() const {
        return Top == -1;
    }

    std::string TopElem() const {
        if (Top < 0) {
            printf("TopElem: stack is empty (string)\n");
            return std::string();
        }
        return S[Top];
    }

    int Size() const {
        return Top + 1;
    }

    void Makenull() {
        Top = -1;
    }
};
