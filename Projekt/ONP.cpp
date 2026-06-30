#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <sstream>
#include "Stos.h"

using namespace std;

bool isNumber(const string &token) { //Funkcja do sprawdzania czy jest cyfrą
	if (token.empty()) return false;
	for (char ch : token) {
		if (!isdigit(static_cast<unsigned char>(ch))) return false;
	}
	return true;
}

bool isOperator(const string &token) { //Funkcja do sprawdzania czy jest to pojedyczny znak operacji
	return token.size() == 1 && (token[0] == '+' || token[0] == '-' ||
								 token[0] == '*' || token[0] == '/' ||
								 token[0] == '^' || token[0] == '~');
}

int precedence(char op) { //priorytety operacji
	switch (op) {
		case '~': return 4;
		case '^': return 3;
		case '*':
		case '/': return 2;
		case '+':
		case '-': return 1;
		default:  return 0;
	}
}

bool isRightAssociative(char op) { //Które operacje są prawostronne
	return op == '^' || op == '~';
}

vector<string> tokenizeInfix(const string &expr) {
	vector<string> tokens;
	string number;
	for (char ch : expr) { //Przechodzimy po każdym znaku expression
		if (isdigit(static_cast<unsigned char>(ch))) { //Jeśli jest liczbą to przepisujemy do string number
			number.push_back(ch);
		}
		else {
			if (!number.empty()) { //Jak nie pusty to dodaje do wektora z tokenami i czyści string
				tokens.push_back(number);
				number.clear();
			}
			if (isspace(static_cast<unsigned char>(ch))) { //Sprawdza czy spacja i jak jest to pomija
				continue;
			}
			if (ch == '+' || ch == '-' || ch == '*' || //Sprawdzamy czy to operator 
				ch == '/' || ch == '^' || ch == '~' ||
				ch == '(' || ch == ')') {
				string t(1, ch);
				tokens.push_back(t); //Jak tak to dodajemy jako string do tokens
			}
		}
	}
	if (!number.empty()) { 
		tokens.push_back(number); 
	}
	return tokens;
}

string infixToRPN(const string &expr) { //Funkcja do zmiany na ONP
	vector<string> tokens = tokenizeInfix(expr); //Włączamy funkcje do zmiany na tokeny
	string token;
	StosString opStack;   
	string output;           
	bool first = true;       

	for (const string &token : tokens) { //Pętla po wszystkich tokenach
		if (isNumber(token)) { //Jeśli liczba nie jest na początku to dodatkowa spacja
			if (!first) output += ' ';
			output += token; //Dodajemy do output i wiemy że następna liczba nie będzie tą początkową
			first = false;
		}
		else if (token == "(") {
			opStack.Push(token); //Jeśli nawias początkowy do dodajemy na stos operatorów
		}
		else if (token == ")") { 
			while (!opStack.Empty() && opStack.TopElem() != "(") { //Jeśli stos nie jest pusty i nie ma szczycie (
				if (!first) output += ' '; //Dodajemy spacje jak nie pierwszy
				output += opStack.TopElem(); //Dopisuje do output pierwszy operator ze stosu
				opStack.Pop(); //Usuwa go ze stosu
				first = false;
			}
			if (!opStack.Empty() && opStack.TopElem() == "(") {
				opStack.Pop(); // zdejmij ( jeśli na szczycie
			}
		}
		else if (isOperator(token)) { //Jeśli operator
			char op = token[0]; //Znak operatora
			while (!opStack.Empty() && isOperator(opStack.TopElem())) { //Dopóki nie pusty stack i na szczycie jakiś operator
				char topOp = opStack.TopElem()[0]; //Operator ze szczytu stosu
				int pTop = precedence(topOp); //Sprawdzamy priorytety
				int pCur = precedence(op);
				bool right = isRightAssociative(op); //I czy prawostronny
				if ((right && pTop > pCur) || (!right && pTop >= pCur)) { //Jeśli operator na stosie operator wyższy lub równy //Dla operacji prawostronnych tylko większy bo
					if (!first) output += ' ';																				   // np dla 2 ^ 3 ^ 2 ma być 2 ^ (3 ^ 2) a nie 
					output += opStack.TopElem(); //Dopisujemy operator z wierzchu											   // (2 ^ 3) ^ 2
					opStack.Pop(); //Usuwamy ze stosu
					first = false;
				} else {
					break;
				}
			}
			opStack.Push(token); //Dodajemy do stosu
		}
	}

	while (!opStack.Empty()) { //Jeśli coś jeszcze jest na stosie
		if (opStack.TopElem() != "(" && opStack.TopElem() != ")") { //Jak nie nawiasy
			if (!first) output += ' ';
			output += opStack.TopElem(); //Dopisz operator z wierzchu 
			first = false;
		}
		opStack.Pop();
	}

	return output;
}

int evaluateRPN(const string &rpn) {
	istringstream iss(rpn);
	string token;
	Stos st;

	while (iss >> token) {
		if (isNumber(token)) { //Jeśli liczba to dodaje na stos
			st.Push(stoi(token));
		}
		else if (isOperator(token)) {
			char op = token[0];
			if (op == '~') {
				if (st.Empty()) throw runtime_error("Błąd ONP: za mało argumentów dla ~"); //Jeśli pusty stos to nie ma na czym wykonać
				int a = st.TopElem(); st.Pop(); //Zdejmujemy ze stosu jedną liczbę
				st.Push(-a); //Odkładamy tą liczbe ale ze zmienionym znakiem
			}
			else {
				if (st.Size() < 2) throw runtime_error("Błąd ONP: za mało argumentów dla operatora binarnego"); //Sprawdzamy czy na stosię są conajmniej dwie liczby
				int b = st.TopElem(); st.Pop(); //Zdejmuje pierwszą a potem drugą liczbe
				int a = st.TopElem(); st.Pop();
				int res = 0;
				switch (op) { //Switch robi dane operacje w zależności od operatora
					case '+': res = a + b; break;
					case '-': res = a - b; break;
					case '*': res = a * b; break;
					case '/':
						if (b == 0) throw runtime_error("Dzielenie przez zero");
						res = a / b; break;
					case '^':
						res = static_cast<int>(pow(a, b));
						break;
				}
				st.Push(res);
			}
		}
	}

	if (st.Size() != 1) throw runtime_error("Błąd ONP: nieprawidłowe wyrażenie"); //Jeśli na stosie nie jest dokładnie jeden element to błąd
	return st.TopElem();
}

int main() {
	string expr;
	cout << "Podaj wyrazenie w notacji tradycyjnej:" << '\n';
	if (!getline(cin, expr)) return 0; 

	string rpn = infixToRPN(expr);
	int result = evaluateRPN(rpn);

	cout << "ONP: ";
	cout << rpn << '\n';
	cout << "Wynik: ";
	cout << result << '\n';

	return 0;
}

