// P2_Mumbaikars
// Devendra Janyani and Jai Patel
// Goal of the project : Writing Dijkstra's algorithm
#include "Edge.h"
#include "Vertex.h"
#include <iostream>
#include <limits>
#include <cstring>  

// Functions
void adjacencymatrix(int** matrix, int size);

void odddegreeV(Vertex* vertices, int size, int*& oddVertices, int& oddCount);

void dijkstra(int** matrix, int source, int size);

int main() {
    int nVertices;
    int nEdges;

    //taking input from file
    std::cin >> nVertices >> nEdges;

    if(std::cin.fail()) {
        std::cout << "Input not found!" << std::endl;
        return 1;
    }

    // Creating vertex array
    Vertex* vertices = new Vertex[nVertices];

    for (int i = 0; i < nVertices; ++i) {
        vertices[i].setIndex(i + 1);
        vertices[i].setDegree(0);
    }

    // Initializing adjacency matrix
    int** adjM = new int*[nVertices];

    for (int i = 0; i < nVertices; ++i) {
        adjM[i] = new int[nVertices];
        std::memset(adjM[i], 0, nVertices * sizeof(int));
    }

    // Reading edges and build the graph
    for (int i = 0; i < nEdges; ++i) {
        int start, end;
        std::cin >> start >> end;
        adjM[start - 1][end - 1] = 1;
        adjM[end - 1][start - 1] = 1;
        vertices[start - 1].setDegree(vertices[start - 1].getDegree() + 1);
        vertices[end - 1].setDegree(vertices[end - 1].getDegree() + 1);
    }

    // Printing adjacency matrix
    std::cout << "The adjacency matrix of the loaded graph G:" << std::endl;
    adjacencymatrix(adjM, nVertices);

    // Identifying odd degree vertices
    int* oddVertices = new int[nVertices];
    int count = 0;

    odddegreeV(vertices, nVertices, oddVertices, count);

    std::cout << "The odd degree vertices in G:" << std::endl;
    std::cout << "O = { ";
    
    for (int i = 0; i < count; ++i) {
        std::cout << oddVertices[i] << " ";
    }
    
    std::cout << "}" << std::endl;

    // Runnning Dijkstra for each odd degree vertex

    for (int i = 0; i < count; ++i) {
        dijkstra(adjM, oddVertices[i] - 1, nVertices);
    }

    // Cleaning up

    for (int i = 0; i < nVertices; ++i) {
        delete[] adjM[i];
    }

    delete[] adjM;

    delete[] vertices;

    delete[] oddVertices;

    return 0;
}



void adjacencymatrix(int** matrix, int size) {

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}


void odddegreeV(Vertex* vertices, int size, int*& oddVertices, int& count) {
    count = 0;

    for (int i = 0; i < size; ++i) {
        if (vertices[i].getDegree() % 2 != 0) {
            oddVertices[count++] = i + 1;
        }
    }

}


void dijkstra(int** matrix, int source, int size) {
    int* dist = new int[size];
    bool* visited = new bool[size];

    for (int i = 0; i < size; i++) {

        dist[i] = std::numeric_limits<int>::max();
        visited[i] = false;

    }

    dist[source] = 0;

    for (int count = 0; count < size - 1; count++) {
        int x = -1;
        
        for (int i = 0; i < size; i++) {

            if (!visited[i] && (x == -1 || dist[i] < dist[x])) {
                x = i;
            }

        }
        visited[x] = true;

        for (int y = 0; y < size; y++) {

            if (!visited[y] && matrix[x][y] && dist[x] != std::numeric_limits<int>::max() && dist[x] + matrix[x][y] < dist[y]) {
                dist[y] = dist[x] + matrix[x][y];
            }

        }
    }



    std::cout << "Single source shortest path lengths from node " << source + 1 << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "  " << i + 1 << ": " << dist[i] << std::endl;
    }

    delete[] dist;

    delete[] visited;
}
