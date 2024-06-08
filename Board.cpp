#include "Board.hpp"

ariel::Board *ariel::Board::instance = nullptr;

ariel::Board::Board()
{
    // ------------------------------    Initialize Edges    ------------------------------
    for (size_t i = 0; i < NUM_OF_EDGES; i++)
    {
        edges.push_back(ariel::Edge(i));
    }

    short id = 0;
    // ------------------------------    Initialize Vertices    ------------------------------

    vertices.push_back(Vertex(SEA, SEA, MOUNTAIN, id++));       // 0
    vertices.push_back(Vertex(SEA, MOUNTAIN, SEA, id++));       // 1
    vertices.push_back(Vertex(SEA, PASTURES, MOUNTAIN, id++));  // 2
    vertices.push_back(Vertex(HILL, PASTURES, MOUNTAIN, id++)); // 3
    vertices.push_back(Vertex(HILL, MOUNTAIN, FIELD, id++));    // 4
    vertices.push_back(Vertex(SEA, FIELD, MOUNTAIN, id++));     // 5
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));       // 6
    vertices.push_back(Vertex(SEA, PASTURES, FOREST, id++));    //7
    vertices.push_back(Vertex(PASTURES, PASTURES, FOREST, id++));   //8
    vertices.push_back(Vertex(PASTURES, PASTURES, HILL, id++));     // 9
    vertices.push_back(Vertex(SEA, SEA, FOREST, id++);          // 10
    vertices.push_back(Vertex(SEA, SEA, FOREST, id++));         // 11
    vertices.push_back(Vertex(SEA, HILL, FOREST, id++));        // 12
    vertices.push_back(Vertex(PASTURES, HILL, FOREST, id++));   // 13
    vertices.push_back(Vertex(PASTURES, HILL, FOREST, id++));   // 14
    vertices.push_back(Vertex(FOREST, HILL, MOUNTAIN, id++));   // 15
    vertices.push_back(Vertex(SEA, HILL, MOUNTAIN, id++));      // 16
    vertices.push_back(Vertex(SEA, SEA, HILL, id++));           // 17
    vertices.push_back(Vertex(DESERT, FOREST, PASTURES, id++)); // 18
    vertices.push_back(Vertex(PASTURES, HILL, DESERT, id++));   // 19
    vertices.push_back(Vertex(FOREST, HILL, DESERT, id++));     // 20
    vertices.push_back(Vertex(FOREST, HILL, FIELD, id++));      // 21
    vertices.push_back(Vertex(FIELD, FIELD, FOREST, id++));     // 22
    vertices.push_back(Vertex(FIELD, FIELD, SEA, id++));        // 23
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));          // 24
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));          // 25
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));          // 26
    vertices.push_back(Vertex(SEA, FIELD, FOREST, id++));       // 27
    vertices.push_back(Vertex(FOREST, FIELD, FOREST, id++));    // 28
    vertices.push_back(Vertex(MOUNTAIN, FOREST, FOREST, id++)); // 29
    vertices.push_back(Vertex(FOREST, DESERT, MOUNTAIN, id++)); // 30
    vertices.push_back(Vertex(DESERT, FIELD, MOUNTAIN, id++));  // 31
    vertices.push_back(Vertex(FOREST, FIELD, DESERT, id++));    // 32
    vertices.push_back(Vertex(PASTURES, FIELD, FOREST, id++));  // 33
    vertices.push_back(Vertex(PASTURES, FOREST, MOUNTAIN, id++));   // 34
    vertices.push_back(Vertex(SEA, PASTURES, MOUNTAIN, id++));  // 35
    vertices.push_back(Vertex(SEA, SEA, MOUNTAIN, id++));     // 36
    vertices.push_back(Vertex(SEA, SEA, MOUNTAIN, id++));     // 37
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));     // 38
    vertices.push_back(Vertex(SEA, PASTURES, PASTURES, id++));     // 39
    vertices.push_back(Vertex(FIELD, PASTURES, PASTURES, id++));     // 40
    vertices.push_back(Vertex(FIELD, FIELD, PASTURES, id++));     // 41
    vertices.push_back(Vertex(FIELD, FIELD, MOUNTAIN, id++));     // 42
    vertices.push_back(Vertex(HILL, FIELD, MOUNTAIN, id++));     // 43
    vertices.push_back(Vertex(FOREST, HILL, MOUNTAIN, id++));     // 44
    vertices.push_back(Vertex(SEA, FOREST, HILL, id++));     // 45
    vertices.push_back(Vertex(SEA, SEA, FOREST, id++));     // 46
    vertices.push_back(Vertex(SEA, SEA, HILL, id++));     // 47
    vertices.push_back(Vertex(SEA, SEA, HILL, id++));     // 48
    vertices.push_back(Vertex(SEA, FIELD, HILL, id++));     // 49
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));     // 50
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));     // 51
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));     // 52
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));     // 53

    // ------------------------------    Initialize Tiles    ------------------------------

    ariel::Edge tile1_e[EDGES_PER_TILE] = {edges.at(0), edges.at(1), edges.at(2), edges.at(3), edges.at(4), edges.at(5)};
    ariel::Vertex tile1_v[VERTICES_PER_TILE];
    ariel::Edge tile2[EDGES_PER_TILE] = { edges.at(0),
                                          edges.at(1),
                                          edges.at(2),
                                          edges.at(3),
                                          edges.at(4),
                                          edges.at(5) }
}

ariel::Board::~Board()
{
    if (instance != nullptr)
        delete instance;
}

ariel::Board *ariel::Board::get_instance()
{
    if (instance == nullptr)
    {
        instance = new Board();
    }
}