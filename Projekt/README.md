# Projekt: Odwrotna Notacja Polska (ONP)

## Opis problemu

Celem programu jest:

- Konwersja wyrażenia arytmetycznego z notacji tradycyjnej do Odwrotnej Notacji Polskiej .
- Obliczenie wartości wyrażenia zapisanego w ONP.

Zakładamy:

- Operujemy na liczbach całkowitych.
- Dozwolone operatory: `+`  `-`  `*`  `/` (tylko dzielenie całkowite)  `^`  `~` (minus unarny).
- Występują nawiasy `(` `)`.
- Program obsługuje wyrażenia ze spacjami i bez.

---

## Pseudokod – obliczanie wartości wyrażenia w ONP

Dla wejścia w ONP:


while (nie_koniec_danych)
{
    pobierz_kolejny_element;
    if (element_jest_operandem)
        wstaw_wartosc_operanda_na_stos;        // PUSH
    else // element jest operatorem
    {
        pobierz_ze_stosu_potrzebne_argumenty;  // POP, odczyt argumentow
        wykonaj_dzialanie;
        wstaw_wynik_na_stos;                   // PUSH
    }
}
// wartosc wyrazenia jest na szczycie stosu



## Pseudokod – konwersja z notacji tradycyjnej do ONP

Dla wejściowego wyrażenia infix:


while (nie_koniec_danych)
{
    wez_kolejny_element;

    if (element_jest_operandem)
        dopisz_element_na_wyjscie;
    else // element jest operatorem lub nawiasem
    {
        if (element_jest_operatorem)
            while (priorytet_operatora_na_stosie >= priorytet_elementu)
                przepisz_operator_ze_stosu_na_wyjscie;   // POP → wyjscie
            wstaw_operator_na_stos;                      // PUSH
        else if (element == "(")
            wstaw_element_na_stos;                       // PUSH
        else if (element == ")")
        {
            // zdejmuj operatorow ze stosu az do "("
            while (na_stosie_operator)
                przepisz_operator_ze_stosu_na_wyjscie;   // POP → wyjscie
            zdejmij_ze_stosu "(";                       // POP
        }
    }
}

while (nie_pusty_stos)
    przepisz_operator_ze_stosu_na_wyjscie;               // POP → wyjscie


## Użyte struktury danych

1. **Stos liczb całkowitych** (`Stos` z pliku `Stos.h`)
    - Własna implementacja stosu oparta na statycznej tablicy `int` o długości `maxlength`.
    - Używany przy obliczaniu wartości wyrażenia w ONP.
    - Operacje: `Push`, `Pop`, `TopElem`, `Empty`, `Size`.

2. **Stos operatorów/nawiasów** (`StosString` z pliku `Stos.h`)
    - Własna implementacja stosu dla `std::string`, również oparta na statycznej tablicy.
    - Używany przy konwersji infix → ONP.
    - Przechowuje operatory i nawiasy.



## Złożoność struktur danych

Dla stosów `Stos` i `StosString` (statyczna tablica o rozmiarze `maxlength`):

- `Push` – czas O(1).
- `Pop` – czas O(1).
- `TopElem` – czas O(1).
- Pamięć całkowita – O(`maxlength`), gdzie `maxlength` jest stałą kompilacji (w kodzie: 100).


## Złożoność głównych algorytmów

### 1. Tokenizacja wyrażenia infix

Wejście: napis długości `L`.

- Przechodzimy po każdym znaku dokładnie raz.
- Operacje na bieżącej liczbie lub wektorze tokenów są O(1).

**Złożoność czasowa:** O(L)  
**Złożoność pamięciowa:** O(L).

### 2. Konwersja infix → ONP

Wejście: `n` tokenów.

- Każdy token jest dokładnie raz przetwarzany.
- Każdy operator jest co najwyżej raz wstawiany i raz zdejmowany ze stosu.

**Złożoność czasowa:** O(n)  
**Złożoność pamięciowa:** O(n).

### 3. Obliczanie wartości wyrażenia w ONP

Wejście: `n` tokenów w ONP.

- Każdy token jest przetwarzany w czasie O(1).
- Każdy operand jest raz wstawiany i co najwyżej raz zdejmowany ze stosu.

**Złożoność czasowa:** O(n)  
**Złożoność pamięciowa:** O(n).



### Kompilacja

g++ ONP.cpp Stos.h -o ONP.exe


### Uruchomienie

./ONP.exe

Program wyświetli komunikat:

"Podaj wyrazenie w notacji tradycyjnej: "


Program poprawnie obsługuje wyrażenia ze spacjami i bez.
W tym miejscu wpisz wyrażenie w notacji tradycyjnej np.:

- `2*(3+3)`
- `23*17-3^5-(6/6)*32-77`
- `2^3^2`
- `~(2+3)*4`

Po wciśnięciu Enter program wypisze:

1. To samo wyrażenie już w ONP.
2. Obliczoną wartość liczbową.

Przykład:

Podaj wyrazenie w notacji tradycyjnej:
23*17-3^5-(2/6)*32-77
ONP: 23 17 * 3 5 ^ - 2 6 / 32 * - 77 -
Wynik: 71
