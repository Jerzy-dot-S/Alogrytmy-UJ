#include "Graf.h"
#include <climits>
#include <queue>
#include <tuple>

std::pair<std::vector<long long>, std::vector<int>> Dijkstra(GraphAsMatrix &g, Vertex *source){ //Algorytm dijkstry
    std::vector<long long> dist(g.NumberOfVertices(), LLONG_MAX/2); //Inicjalizacja
    std::vector<int> parent(g.NumberOfVertices(), -1);
    int s = source->Number();
    dist[s] = 0;
    std::priority_queue<std::pair<long long,int>, std::vector<std::pair<long long,int>>, std::greater<std::pair<long long,int>>> priority_queue; //Kolejka priorytetowa z parami, najmniejszy na początku
    priority_queue.emplace(0,s); //Wkłada na kolejke parę (0,s)

    while (!priority_queue.empty()) {
        auto [d, v] = priority_queue.top(); priority_queue.pop(); //bierzemy element z kolejki 
        if (d != dist[v]) continue;
        Iterator<Edge>& iterator = g.EmanatingEdgesIter(v); //Iterator po wszystkich krawędziach
        while (!iterator.IsDone()) {
            Edge &edge = *iterator;
            Vertex *vx = edge.Mate(g.SelectVertex(v)); //Wybiera sąsiada v
            int to = vx->Number();
            long long w = edge.weight;
            if (dist[v] + w < dist[to]) { //Czy ścieżka jest krótsza niż obecna
                dist[to] = dist[v] + w; //Jak tak to aktualizujemy
                parent[to] = v; //Jak sie dostać do to
                priority_queue.emplace(dist[to], to); //I dodajemy do kolejki 
            }
            ++iterator;
        }
        delete &iterator;
    }
    return {dist, parent}; //Zwraca dystanse i skąd dojść
}

int main() {
    int n;
    std::cin >> n; //Liczba metali/wierzchołków

    std::vector<long long> ceny(n + 1, 0); 
    for (int i = 1; i <= n; i++) {
        std::cin >> ceny[i]; //Ceny dla metali/wagi dla wierzchołków
    }
    
    int liczbaPrzemian;
    std::cin >> liczbaPrzemian; 

    GraphAsMatrix graph(n + 1, true);
    GraphAsMatrix reverseGraph(n + 1, true); //Odwrócony graph do sprawdzenia drogi powrotnej 

    for (int i = 0; i < liczbaPrzemian; i++) {
        int a, b, c;
        std::cin >> a >> b >> c; //Przemiany i cena

        graph.AddEdge(a, b); 
        Edge* e = graph.SelectEdge(a, b);
        e->weight = c;

        reverseGraph.AddEdge(b, a);
        Edge* re = reverseGraph.SelectEdge(b, a);
        re->weight = c;
    }

    auto [distFromGold, parentFromGold] = Dijkstra(graph, graph.SelectVertex(1));
    auto [distToGold, parentToGold] = Dijkstra(reverseGraph, reverseGraph.SelectVertex(1));

    const long long INF = LLONG_MAX / 2;
    long long wynik = INF;
    for (int i = 1; i <= n; i++) { //Pętla do sprawdzania najmniejszego kosztu
        if (distFromGold[i] >= INF || distToGold[i] >= INF) {
            continue;
        }
        long long koszt = distFromGold[i] + distToGold[i] + (ceny[i] / 2); //Trasa tam i z powrotem + cło
        if (koszt < wynik) {
            wynik = koszt;
        }
    }

    std::cout << wynik << '\n';

    return 0;
}