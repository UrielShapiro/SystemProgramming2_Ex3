#include "Board.hpp"

using namespace GameConsts;

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

    vertices.push_back(Vertex(SEA, SEA, MOUNTAIN, id++));         // 0
    vertices.push_back(Vertex(SEA, MOUNTAIN, SEA, id++));         // 1
    vertices.push_back(Vertex(SEA, PASTURES, MOUNTAIN, id++));    // 2
    vertices.push_back(Vertex(HILL, PASTURES, MOUNTAIN, id++));   // 3
    vertices.push_back(Vertex(HILL, MOUNTAIN, FIELD, id++));      // 4
    vertices.push_back(Vertex(SEA, FIELD, MOUNTAIN, id++));       // 5
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));         // 6
    vertices.push_back(Vertex(SEA, PASTURES, FOREST, id++));      // 7
    vertices.push_back(Vertex(PASTURES, PASTURES, FOREST, id++)); // 8
    vertices.push_back(Vertex(PASTURES, PASTURES, HILL, id++));   // 9
    vertices.push_back(Vertex(SEA, SEA, FOREST, id++));           // 10
    vertices.push_back(Vertex(SEA, SEA, FOREST, id++));           // 11
    vertices.push_back(Vertex(SEA, HILL, FOREST, id++));          // 12
    vertices.push_back(Vertex(PASTURES, HILL, FOREST, id++));     // 13
    vertices.push_back(Vertex(PASTURES, HILL, FOREST, id++));     // 14
    vertices.push_back(Vertex(FOREST, HILL, MOUNTAIN, id++));     // 15
    vertices.push_back(Vertex(SEA, HILL, MOUNTAIN, id++));        // 16
    vertices.push_back(Vertex(SEA, SEA, HILL, id++));             // 17
    vertices.push_back(Vertex(DESERT, FOREST, PASTURES, id++));   // 18
    vertices.push_back(Vertex(PASTURES, HILL, DESERT, id++));     // 19
    vertices.push_back(Vertex(FOREST, HILL, DESERT, id++));       // 20
    vertices.push_back(Vertex(FOREST, HILL, FIELD, id++));        // 21
    vertices.push_back(Vertex(FIELD, FIELD, FOREST, id++));       // 22
    vertices.push_back(Vertex(FIELD, FIELD, SEA, id++));          // 23
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));            // 24
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));            // 25
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));            // 26
    vertices.push_back(Vertex(SEA, FIELD, FOREST, id++));         // 27
    vertices.push_back(Vertex(FOREST, FIELD, FOREST, id++));      // 28
    vertices.push_back(Vertex(MOUNTAIN, FOREST, FOREST, id++));   // 29
    vertices.push_back(Vertex(FOREST, DESERT, MOUNTAIN, id++));   // 30
    vertices.push_back(Vertex(DESERT, FIELD, MOUNTAIN, id++));    // 31
    vertices.push_back(Vertex(FOREST, FIELD, DESERT, id++));      // 32
    vertices.push_back(Vertex(PASTURES, FIELD, FOREST, id++));    // 33
    vertices.push_back(Vertex(PASTURES, FOREST, MOUNTAIN, id++)); // 34
    vertices.push_back(Vertex(SEA, PASTURES, MOUNTAIN, id++));    // 35
    vertices.push_back(Vertex(SEA, SEA, MOUNTAIN, id++));         // 36
    vertices.push_back(Vertex(SEA, SEA, MOUNTAIN, id++));         // 37
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));         // 38
    vertices.push_back(Vertex(SEA, PASTURES, PASTURES, id++));    // 39
    vertices.push_back(Vertex(FIELD, PASTURES, PASTURES, id++));  // 40
    vertices.push_back(Vertex(FIELD, FIELD, PASTURES, id++));     // 41
    vertices.push_back(Vertex(FIELD, FIELD, MOUNTAIN, id++));     // 42
    vertices.push_back(Vertex(HILL, FIELD, MOUNTAIN, id++));      // 43
    vertices.push_back(Vertex(FOREST, HILL, MOUNTAIN, id++));     // 44
    vertices.push_back(Vertex(SEA, FOREST, HILL, id++));          // 45
    vertices.push_back(Vertex(SEA, SEA, FOREST, id++));           // 46
    vertices.push_back(Vertex(SEA, SEA, HILL, id++));             // 47
    vertices.push_back(Vertex(SEA, SEA, HILL, id++));             // 48
    vertices.push_back(Vertex(SEA, FIELD, HILL, id++));           // 49
    vertices.push_back(Vertex(SEA, SEA, FIELD, id++));            // 50
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));         // 51
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));         // 52
    vertices.push_back(Vertex(SEA, SEA, PASTURES, id++));         // 53

    // ------------------------------    Initialize Tiles    ------------------------------

    short v_number = 0;

    ariel::Edge tile1_e[EDGES_PER_TILE] = {edges.at(0), edges.at(1), edges.at(2), edges.at(3), edges.at(4), edges.at(5)};
    ariel::Vertex tile1_v[VERTICES_PER_TILE] = {vertices.at(0), vertices.at(1), vertices.at(2),
                                                vertices.at(3), vertices.at(4), vertices.at(5)};
    tiles.push_back(ariel::Tile(v_number++, 10, MOUNTAIN, tile1_e, tile1_v));

    ariel::Edge tile2_e[EDGES_PER_TILE] = {edges.at(6), edges.at(7), edges.at(8), edges.at(9), edges.at(10), edges.at(2)};
    ariel::Vertex tile2_v[VERTICES_PER_TILE] = {vertices.at(2), vertices.at(6), vertices.at(7),
                                                vertices.at(8), vertices.at(9), vertices.at(3)};
    tiles.push_back(ariel::Tile(v_number++, 2, PASTURES, tile2_e, tile2_v));

    ariel::Edge tile3_e[EDGES_PER_TILE] = {edges.at(11), edges.at(12), edges.at(13), edges.at(14), edges.at(15), edges.at(8)};
    ariel::Vertex tile3_v[VERTICES_PER_TILE] = {vertices.at(7), vertices.at(10), vertices.at(11),
                                                vertices.at(12), vertices.at(13), vertices.at(8)};
    tiles.push_back(ariel::Tile(v_number++, 9, FOREST, tile3_e, tile3_v));

    ariel::Edge tile4_e[EDGES_PER_TILE] = {edges.at(14), edges.at(16), edges.at(17), edges.at(18), edges.at(19), edges.at(20)};
    ariel::Vertex tile4_v[VERTICES_PER_TILE] = {vertices.at(13), vertices.at(12), vertices.at(17),
                                                vertices.at(16), vertices.at(15), vertices.at(14)};
    tiles.push_back(ariel::Tile(v_number++, 10, HILL, tile4_e, tile4_v));

    ariel::Edge tile5_e[EDGES_PER_TILE] = {edges.at(9), edges.at(15), edges.at(20), edges.at(21), edges.at(22), edges.at(23)};
    ariel::Vertex tile5_v[VERTICES_PER_TILE] = {vertices.at(9), vertices.at(8), vertices.at(13),
                                                vertices.at(14), vertices.at(18), vertices.at(19)};
    tiles.push_back(ariel::Tile(v_number++, 4, PASTURES, tile5_e, tile5_v));

    ariel::Edge tile6_e[EDGES_PER_TILE] = {edges.at(3), edges.at(10), edges.at(23), edges.at(24), edges.at(25), edges.at(26)};
    ariel::Vertex tile6_v[VERTICES_PER_TILE] = {vertices.at(4), vertices.at(3), vertices.at(9),
                                                vertices.at(19), vertices.at(20), vertices.at(21)};
    tiles.push_back(ariel::Tile(v_number++, 6, HILL, tile6_e, tile6_v));

    ariel::Edge tile7_e[EDGES_PER_TILE] = {edges.at(30), edges.at(4), edges.at(26), edges.at(27), edges.at(28), edges.at(29)};
    ariel::Vertex tile7_v[VERTICES_PER_TILE] = {vertices.at(24), vertices.at(5), vertices.at(4),
                                                vertices.at(21), vertices.at(22), vertices.at(23)};
    tiles.push_back(ariel::Tile(v_number++, 12, FIELD, tile7_e, tile7_v));

    ariel::Edge tile8_e[EDGES_PER_TILE] = {edges.at(31), edges.at(28), edges.at(32), edges.at(33), edges.at(34), edges.at(35)};
    ariel::Vertex tile8_v[VERTICES_PER_TILE] = {vertices.at(25), vertices.at(23), vertices.at(22),
                                                vertices.at(28), vertices.at(27), vertices.at(26)};
    tiles.push_back(ariel::Tile(v_number++, 9, FIELD, tile8_e, tile8_v));

    ariel::Edge tile9_e[EDGES_PER_TILE] = {edges.at(27), edges.at(25), edges.at(38), edges.at(37), edges.at(36), edges.at(32)};
    ariel::Vertex tile9_v[VERTICES_PER_TILE] = {vertices.at(22), vertices.at(21), vertices.at(20),
                                                vertices.at(30), vertices.at(29), vertices.at(28)};
    tiles.push_back(ariel::Tile(v_number++, 11, FOREST, tile9_e, tile9_v));

    ariel::Edge tile10_e[EDGES_PER_TILE] = {edges.at(24), edges.at(22), edges.at(41), edges.at(40), edges.at(39), edges.at(38)};
    ariel::Vertex tile10_v[VERTICES_PER_TILE] = {vertices.at(20), vertices.at(19), vertices.at(18),
                                                 vertices.at(32), vertices.at(31), vertices.at(30)};
    tiles.push_back(ariel::Tile(v_number++, 7, DESERT, tile10_e, tile10_v));

    ariel::Edge tile11_e[EDGES_PER_TILE] = {edges.at(21), edges.at(19), edges.at(44), edges.at(43), edges.at(42), edges.at(41)};
    ariel::Vertex tile11_v[VERTICES_PER_TILE] = {vertices.at(18), vertices.at(14), vertices.at(15),
                                                 vertices.at(34), vertices.at(33), vertices.at(32)};
    tiles.push_back(ariel::Tile(v_number++, 3, FOREST, tile11_e, tile11_v));

    ariel::Edge tile12_e[EDGES_PER_TILE] = {edges.at(18), edges.at(48), edges.at(47), edges.at(46), edges.at(45), edges.at(44)};
    ariel::Vertex tile12_v[VERTICES_PER_TILE] = {vertices.at(15), vertices.at(16), vertices.at(37),
                                                 vertices.at(36), vertices.at(35), vertices.at(34)};
    tiles.push_back(ariel::Tile(v_number++, 8, MOUNTAIN, tile12_e, tile12_v));

    ariel::Edge tile13_e[EDGES_PER_TILE] = {edges.at(33), edges.at(36), edges.at(58), edges.at(59), edges.at(60), edges.at(61)};
    ariel::Vertex tile13_v[VERTICES_PER_TILE] = {vertices.at(27), vertices.at(28), vertices.at(29),
                                                 vertices.at(44), vertices.at(45), vertices.at(46)};
    tiles.push_back(ariel::Tile(v_number++, 8, FOREST, tile13_e, tile13_v));

    ariel::Edge tile14_e[EDGES_PER_TILE] = {edges.at(37), edges.at(39), edges.at(55), edges.at(56), edges.at(57), edges.at(58)};
    ariel::Vertex tile14_v[VERTICES_PER_TILE] = {vertices.at(29), vertices.at(30), vertices.at(31),
                                                 vertices.at(42), vertices.at(43), vertices.at(44)};
    tiles.push_back(ariel::Tile(v_number++, 3, MOUNTAIN, tile14_e, tile14_v));

    ariel::Edge tile15_e[EDGES_PER_TILE] = {edges.at(40), edges.at(42), edges.at(52), edges.at(53), edges.at(54), edges.at(55)};
    ariel::Vertex tile15_v[VERTICES_PER_TILE] = {vertices.at(31), vertices.at(32), vertices.at(33),
                                                 vertices.at(40), vertices.at(41), vertices.at(42)};
    tiles.push_back(ariel::Tile(v_number++, 4, FIELD, tile15_e, tile15_v));

    ariel::Edge tile16_e[EDGES_PER_TILE] = {edges.at(43), edges.at(45), edges.at(49), edges.at(50), edges.at(51), edges.at(52)};
    ariel::Vertex tile16_v[VERTICES_PER_TILE] = {vertices.at(33), vertices.at(34), vertices.at(35),
                                                 vertices.at(38), vertices.at(39), vertices.at(40)};
    tiles.push_back(ariel::Tile(v_number++, 5, PASTURES, tile16_e, tile16_v));

    ariel::Edge tile17_e[EDGES_PER_TILE] = {edges.at(53), edges.at(51), edges.at(72), edges.at(71), edges.at(70), edges.at(68)};
    ariel::Vertex tile17_v[VERTICES_PER_TILE] = {vertices.at(41), vertices.at(40), vertices.at(39),
                                                 vertices.at(53), vertices.at(52), vertices.at(51)};
    tiles.push_back(ariel::Tile(v_number++, 11, PASTURES, tile17_e, tile17_v));

    ariel::Edge tile18_e[EDGES_PER_TILE] = {edges.at(56), edges.at(54), edges.at(68), edges.at(67), edges.at(66), edges.at(65)};
    ariel::Vertex tile18_v[VERTICES_PER_TILE] = {vertices.at(43), vertices.at(42), vertices.at(41),
                                                 vertices.at(51), vertices.at(50), vertices.at(49)};
    tiles.push_back(ariel::Tile(v_number++, 6, FIELD, tile18_e, tile18_v));

    ariel::Edge tile19_e[EDGES_PER_TILE] = {edges.at(59), edges.at(57), edges.at(65), edges.at(64), edges.at(63), edges.at(62)};
    ariel::Vertex tile19_v[VERTICES_PER_TILE] = {vertices.at(45), vertices.at(44), vertices.at(43),
                                                 vertices.at(49), vertices.at(48), vertices.at(47)};
    tiles.push_back(ariel::Tile(v_number++, 5, HILL, tile19_e, tile19_v));
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

// To avoid reaching over the vector boundries or attempting to reach negative cell in the cell
size_t good_mod(size_t mod, int base)
{
    return ((mod % base) + base) % base;
}

bool ariel::Board::valid_settlement_placement(Vertex &v, Player &p)
{
    if (!v.is_free()) // If the place is not free, check if the owner is the same.
    {
        return v.get_building()->get_owner().get_id() == p.get_id();
    }

    bool valid1 = false;
    for (ariel::Tile &t : this->tiles) // Finding all of the tiles that vertex is adjecent to
    {
        if (std::find(t.get_vertices().begin(), t.get_vertices().end(), v) != t.get_vertices().end()) // If not found, an iterator to the end will be returned.
        {
            for (size_t i = 0; i < VERTICES_PER_TILE; i++)
            {
                if (t.get_vertices().at(i)->get_id() == v.get_id())
                {

                    // Check if it's neighbour vertex has a village/city of other player
                    if (!t.get_vertices().at(good_mod(i + 1, VERTICES_PER_TILE))->is_free() &&
                        t.get_vertices().at(good_mod(i + 1, VERTICES_PER_TILE))->get_building()->get_owner().get_id() != p.get_id())
                    {
                        return false;
                    }

                    if (!t.get_vertices().at(good_mod(i - 1, VERTICES_PER_TILE))->is_free() &&
                        t.get_vertices().at(good_mod(i - 1, VERTICES_PER_TILE))->get_building()->get_owner().get_id() != p.get_id())
                    {
                        return false;
                    }

                    // Check if theres a road to that vertex
                    if (t.get_edges().at(i)->isTaken() && t.get_edges().at(i)->get_owner()->get_id() == p.get_id())
                    {
                        return true;
                    }

                    if (t.get_edges().at(good_mod(i - 1, EDGES_PER_TILE))->isTaken() &&
                        t.get_edges().at(good_mod(i - 1, EDGES_PER_TILE))->get_owner()->get_id() == p.get_id())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false; // If there's no road to that vertex from each of its adjecent tiles, return false
}

bool ariel::Board::valid_road_placement(Edge &e, Player &p)
{
    if (e.isTaken())
    {
        return false;
    }
    bool valid1 = false;
    bool valid2 = false;
    bool has_village = false;
    for (ariel::Tile &t : this->tiles)
    {
        if (std::find(t.get_edges().begin(), t.get_edges().end(), e) != t.get_edges().end()) // If not found, an iterator to the end will be returned.
        {
            for (size_t i = 0; i < EDGES_PER_TILE; i++)
            {
                if (t.get_edges().at(i)->get_id() == e.get_id())
                {
                    // Check the edge adjecent edges
                    if (t.get_edges().at(good_mod(i - 1, EDGES_PER_TILE))->get_owner() == nullptr) // If this place has no road yet
                    {
                        continue;
                    }
                    if (!t.get_edges().at(good_mod(i - 1, EDGES_PER_TILE))->get_owner()->get_id() == p.get_id()) // i - 1 might be a nagative number
                        valid1 = true;

                    if (t.get_edges().at(good_mod(i + 1, EDGES_PER_TILE))->get_owner() == nullptr) // If this place has no road yet
                    {
                        continue;
                    }
                    if (!t.get_edges().at(good_mod(i + 1, EDGES_PER_TILE))->get_owner()->get_id() == p.get_id()) // i + 1 might be > EDGES_PER_TILE
                        valid2 = true;

                    // Checking if theres an adjecent village / city
                    if (!t.get_vertices().at(i)->is_free())
                    {
                        has_village = t.get_vertices().at(i)->get_building()->get_owner().get_id() == p.get_id();
                    }

                    if (!t.get_vertices().at(good_mod(i + 1, VERTICES_PER_TILE))->is_free())
                    {
                        has_village = t.get_vertices().at(i)->get_building()->get_owner().get_id() == p.get_id();
                    }

                    break;
                }
                if (valid1 || valid2 || has_village)
                {
                    return true;
                }
                // Else: check other vertices who own that edge
            }
        }
    }
    return false; // If there isn't a village on a vertex near that edge or it's adjecent edges does not have a road owned by that player
}

std::vector<ariel::Tile> ariel::Board::get_tiles()
{
    return this->tiles;
}

std::vector<ariel::Edge> ariel::Board::get_edges()
{
    return this->edges;
}
