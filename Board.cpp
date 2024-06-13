#include "Board.hpp"
#include <algorithm>

using GameConsts::MapValues;

ariel::Board *ariel::Board::instance = nullptr;

ariel::Board::Board()
{
    // ------------------------------    Initialize Edges    ------------------------------
    for (size_t i = 0; i < NUM_OF_EDGES; i++)
    {
        edges.push_back(new ariel::Edge(i));
    }

    short id = 0;
    // ------------------------------    Initialize Vertices    ------------------------------

    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::MOUNTAIN, id++));         // 0
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::MOUNTAIN, GameConsts::MapValues::SEA, id++));         // 1
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, GameConsts::MapValues::MOUNTAIN, id++));    // 2
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::HILL, GameConsts::MapValues::PASTURES, GameConsts::MapValues::MOUNTAIN, id++));   // 3
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::HILL, GameConsts::MapValues::MOUNTAIN, GameConsts::MapValues::FIELD, id++));      // 4
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, GameConsts::MapValues::MOUNTAIN, id++));       // 5
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, id++));         // 6
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, GameConsts::MapValues::FOREST, id++));      // 7
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::PASTURES, GameConsts::MapValues::FOREST, id++)); // 8
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::PASTURES, GameConsts::MapValues::HILL, id++));   // 9
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FOREST, id++));           // 10
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FOREST, id++));           // 11
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::HILL, GameConsts::MapValues::FOREST, id++));          // 12
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::HILL, GameConsts::MapValues::FOREST, id++));     // 13
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::HILL, GameConsts::MapValues::FOREST, id++));     // 14
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::HILL, GameConsts::MapValues::MOUNTAIN, id++));     // 15
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::HILL, GameConsts::MapValues::MOUNTAIN, id++));        // 16
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::HILL, id++));             // 17
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::DESERT, GameConsts::MapValues::FOREST, GameConsts::MapValues::PASTURES, id++));   // 18
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::HILL, GameConsts::MapValues::DESERT, id++));     // 19
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::HILL, GameConsts::MapValues::DESERT, id++));       // 20
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::HILL, GameConsts::MapValues::FIELD, id++));        // 21
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FIELD, GameConsts::MapValues::FIELD, GameConsts::MapValues::FOREST, id++));       // 22
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FIELD, GameConsts::MapValues::FIELD, GameConsts::MapValues::SEA, id++));          // 23
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, id++));            // 24
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, id++));            // 25
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, id++));            // 26
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, GameConsts::MapValues::FOREST, id++));         // 27
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::FIELD, GameConsts::MapValues::FOREST, id++));      // 28
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::MOUNTAIN, GameConsts::MapValues::FOREST, GameConsts::MapValues::FOREST, id++));   // 29
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::MOUNTAIN, id++));   // 30
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::DESERT, GameConsts::MapValues::FIELD, GameConsts::MapValues::MOUNTAIN, id++));    // 31
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::FIELD, GameConsts::MapValues::DESERT, id++));      // 32
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::FIELD, GameConsts::MapValues::FOREST, id++));    // 33
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::PASTURES, GameConsts::MapValues::FOREST, GameConsts::MapValues::MOUNTAIN, id++)); // 34
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, GameConsts::MapValues::MOUNTAIN, id++));    // 35
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::MOUNTAIN, id++));         // 36
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::MOUNTAIN, id++));         // 37
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, id++));         // 38
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, GameConsts::MapValues::PASTURES, id++));    // 39
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FIELD, GameConsts::MapValues::PASTURES, GameConsts::MapValues::PASTURES, id++));  // 40
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FIELD, GameConsts::MapValues::FIELD, GameConsts::MapValues::PASTURES, id++));     // 41
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FIELD, GameConsts::MapValues::FIELD, GameConsts::MapValues::MOUNTAIN, id++));     // 42
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::HILL, GameConsts::MapValues::FIELD, GameConsts::MapValues::MOUNTAIN, id++));      // 43
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::FOREST, GameConsts::MapValues::HILL, GameConsts::MapValues::MOUNTAIN, id++));     // 44
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::FOREST, GameConsts::MapValues::HILL, id++));          // 45
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FOREST, id++));           // 46
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::HILL, id++));             // 47
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::HILL, id++));             // 48
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, GameConsts::MapValues::HILL, id++));           // 49
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::FIELD, id++));            // 50
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, id++));         // 51
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, id++));         // 52
    vertices.push_back(new ariel::Vertex(GameConsts::MapValues::SEA, GameConsts::MapValues::SEA, GameConsts::MapValues::PASTURES, id++));         // 53

    // ------------------------------    Initialize Tiles    ------------------------------

    short v_number = 0;

    ariel::Edge *tile1_e[EDGES_PER_TILE] = {edges.at(0), edges.at(1), edges.at(2), edges.at(3), edges.at(4), edges.at(5)};
    ariel::Vertex *tile1_v[VERTICES_PER_TILE] = {vertices.at(0), vertices.at(1), vertices.at(2),
                                                 vertices.at(3), vertices.at(4), vertices.at(5)};
    tiles.push_back(new ariel::Tile(v_number++, 10, GameConsts::MapValues::MOUNTAIN, tile1_e, tile1_v));

    ariel::Edge *tile2_e[EDGES_PER_TILE] = {edges.at(6), edges.at(7), edges.at(8), edges.at(9), edges.at(10), edges.at(2)};
    ariel::Vertex *tile2_v[VERTICES_PER_TILE] = {vertices.at(2), vertices.at(6), vertices.at(7),
                                                 vertices.at(8), vertices.at(9), vertices.at(3)};
    tiles.push_back(new ariel::Tile(v_number++, 2, GameConsts::MapValues::PASTURES, tile2_e, tile2_v));

    ariel::Edge *tile3_e[EDGES_PER_TILE] = {edges.at(11), edges.at(12), edges.at(13), edges.at(14), edges.at(15), edges.at(8)};
    ariel::Vertex *tile3_v[VERTICES_PER_TILE] = {vertices.at(7), vertices.at(10), vertices.at(11),
                                                 vertices.at(12), vertices.at(13), vertices.at(8)};
    tiles.push_back(new ariel::Tile(v_number++, 9, GameConsts::MapValues::FOREST, tile3_e, tile3_v));

    ariel::Edge *tile4_e[EDGES_PER_TILE] = {edges.at(14), edges.at(16), edges.at(17), edges.at(18), edges.at(19), edges.at(20)};
    ariel::Vertex *tile4_v[VERTICES_PER_TILE] = {vertices.at(13), vertices.at(12), vertices.at(17),
                                                 vertices.at(16), vertices.at(15), vertices.at(14)};
    tiles.push_back(new ariel::Tile(v_number++, 10, GameConsts::MapValues::HILL, tile4_e, tile4_v));

    ariel::Edge *tile5_e[EDGES_PER_TILE] = {edges.at(9), edges.at(15), edges.at(20), edges.at(21), edges.at(22), edges.at(23)};
    ariel::Vertex *tile5_v[VERTICES_PER_TILE] = {vertices.at(9), vertices.at(8), vertices.at(13),
                                                 vertices.at(14), vertices.at(18), vertices.at(19)};
    tiles.push_back(new ariel::Tile(v_number++, 4, GameConsts::MapValues::PASTURES, tile5_e, tile5_v));

    ariel::Edge *tile6_e[EDGES_PER_TILE] = {edges.at(3), edges.at(10), edges.at(23), edges.at(24), edges.at(25), edges.at(26)};
    ariel::Vertex *tile6_v[VERTICES_PER_TILE] = {vertices.at(4), vertices.at(3), vertices.at(9),
                                                 vertices.at(19), vertices.at(20), vertices.at(21)};
    tiles.push_back(new ariel::Tile(v_number++, 6, GameConsts::MapValues::HILL, tile6_e, tile6_v));

    ariel::Edge *tile7_e[EDGES_PER_TILE] = {edges.at(30), edges.at(4), edges.at(26), edges.at(27), edges.at(28), edges.at(29)};
    ariel::Vertex *tile7_v[VERTICES_PER_TILE] = {vertices.at(24), vertices.at(5), vertices.at(4),
                                                 vertices.at(21), vertices.at(22), vertices.at(23)};
    tiles.push_back(new ariel::Tile(v_number++, 12, GameConsts::MapValues::FIELD, tile7_e, tile7_v));

    ariel::Edge *tile8_e[EDGES_PER_TILE] = {edges.at(31), edges.at(28), edges.at(32), edges.at(33), edges.at(34), edges.at(35)};
    ariel::Vertex *tile8_v[VERTICES_PER_TILE] = {vertices.at(25), vertices.at(23), vertices.at(22),
                                                 vertices.at(28), vertices.at(27), vertices.at(26)};
    tiles.push_back(new ariel::Tile(v_number++, 9, GameConsts::MapValues::FIELD, tile8_e, tile8_v));

    ariel::Edge *tile9_e[EDGES_PER_TILE] = {edges.at(27), edges.at(25), edges.at(38), edges.at(37), edges.at(36), edges.at(32)};
    ariel::Vertex *tile9_v[VERTICES_PER_TILE] = {vertices.at(22), vertices.at(21), vertices.at(20),
                                                 vertices.at(30), vertices.at(29), vertices.at(28)};
    tiles.push_back(new ariel::Tile(v_number++, 11, GameConsts::MapValues::FOREST, tile9_e, tile9_v));

    ariel::Edge *tile10_e[EDGES_PER_TILE] = {edges.at(24), edges.at(22), edges.at(41), edges.at(40), edges.at(39), edges.at(38)};
    ariel::Vertex *tile10_v[VERTICES_PER_TILE] = {vertices.at(20), vertices.at(19), vertices.at(18),
                                                  vertices.at(32), vertices.at(31), vertices.at(30)};
    tiles.push_back(new ariel::Tile(v_number++, 7, GameConsts::MapValues::DESERT, tile10_e, tile10_v));

    ariel::Edge *tile11_e[EDGES_PER_TILE] = {edges.at(21), edges.at(19), edges.at(44), edges.at(43), edges.at(42), edges.at(41)};
    ariel::Vertex *tile11_v[VERTICES_PER_TILE] = {vertices.at(18), vertices.at(14), vertices.at(15),
                                                  vertices.at(34), vertices.at(33), vertices.at(32)};
    tiles.push_back(new ariel::Tile(v_number++, 3, GameConsts::MapValues::FOREST, tile11_e, tile11_v));

    ariel::Edge *tile12_e[EDGES_PER_TILE] = {edges.at(18), edges.at(48), edges.at(47), edges.at(46), edges.at(45), edges.at(44)};
    ariel::Vertex *tile12_v[VERTICES_PER_TILE] = {vertices.at(15), vertices.at(16), vertices.at(37),
                                                  vertices.at(36), vertices.at(35), vertices.at(34)};
    tiles.push_back(new ariel::Tile(v_number++, 8, GameConsts::MapValues::MOUNTAIN, tile12_e, tile12_v));

    ariel::Edge *tile13_e[EDGES_PER_TILE] = {edges.at(33), edges.at(36), edges.at(58), edges.at(59), edges.at(60), edges.at(61)};
    ariel::Vertex *tile13_v[VERTICES_PER_TILE] = {vertices.at(27), vertices.at(28), vertices.at(29),
                                                  vertices.at(44), vertices.at(45), vertices.at(46)};
    tiles.push_back(new ariel::Tile(v_number++, 8, GameConsts::MapValues::FOREST, tile13_e, tile13_v));

    ariel::Edge *tile14_e[EDGES_PER_TILE] = {edges.at(37), edges.at(39), edges.at(55), edges.at(56), edges.at(57), edges.at(58)};
    ariel::Vertex *tile14_v[VERTICES_PER_TILE] = {vertices.at(29), vertices.at(30), vertices.at(31),
                                                  vertices.at(42), vertices.at(43), vertices.at(44)};
    tiles.push_back(new ariel::Tile(v_number++, 3, GameConsts::MapValues::MOUNTAIN, tile14_e, tile14_v));

    ariel::Edge *tile15_e[EDGES_PER_TILE] = {edges.at(40), edges.at(42), edges.at(52), edges.at(53), edges.at(54), edges.at(55)};
    ariel::Vertex *tile15_v[VERTICES_PER_TILE] = {vertices.at(31), vertices.at(32), vertices.at(33),
                                                  vertices.at(40), vertices.at(41), vertices.at(42)};
    tiles.push_back(new ariel::Tile(v_number++, 4, GameConsts::MapValues::FIELD, tile15_e, tile15_v));

    ariel::Edge *tile16_e[EDGES_PER_TILE] = {edges.at(43), edges.at(45), edges.at(49), edges.at(50), edges.at(51), edges.at(52)};
    ariel::Vertex *tile16_v[VERTICES_PER_TILE] = {vertices.at(33), vertices.at(34), vertices.at(35),
                                                  vertices.at(38), vertices.at(39), vertices.at(40)};
    tiles.push_back(new ariel::Tile(v_number++, 5, GameConsts::MapValues::PASTURES, tile16_e, tile16_v));

    ariel::Edge *tile17_e[EDGES_PER_TILE] = {edges.at(53), edges.at(51), edges.at(72), edges.at(71), edges.at(70), edges.at(68)};
    ariel::Vertex *tile17_v[VERTICES_PER_TILE] = {vertices.at(41), vertices.at(40), vertices.at(39),
                                                  vertices.at(53), vertices.at(52), vertices.at(51)};
    tiles.push_back(new ariel::Tile(v_number++, 11, GameConsts::MapValues::PASTURES, tile17_e, tile17_v));

    ariel::Edge *tile18_e[EDGES_PER_TILE] = {edges.at(56), edges.at(54), edges.at(68), edges.at(67), edges.at(66), edges.at(65)};
    ariel::Vertex *tile18_v[VERTICES_PER_TILE] = {vertices.at(43), vertices.at(42), vertices.at(41),
                                                  vertices.at(51), vertices.at(50), vertices.at(49)};
    tiles.push_back(new ariel::Tile(v_number++, 6, GameConsts::MapValues::FIELD, tile18_e, tile18_v));

    ariel::Edge *tile19_e[EDGES_PER_TILE] = {edges.at(59), edges.at(57), edges.at(65), edges.at(64), edges.at(63), edges.at(62)};
    ariel::Vertex *tile19_v[VERTICES_PER_TILE] = {vertices.at(45), vertices.at(44), vertices.at(43),
                                                  vertices.at(49), vertices.at(48), vertices.at(47)};
    tiles.push_back(new ariel::Tile(v_number++, 5, GameConsts::MapValues::HILL, tile19_e, tile19_v));
}

ariel::Board::~Board()
{
    if (instance != nullptr)
    {
        for (ariel::Vertex *v : vertices)
        {
            delete v;
        }
        
        for (ariel::Edge *e : edges)
        {
            delete e;
        }
        for (ariel::Tile *tile : tiles)
        {
            delete tile;
        }
        instance = nullptr;
    }
}

ariel::Board *ariel::Board::get_instance()
{
    if (instance == nullptr)
    {
        instance = new Board();
    }
    return instance;
}



bool ariel::Board::valid_settlement_placement(Vertex &v, Player &p)
{
    if (!v.is_free()) // If the place is not free, check if the owner is the same.
    {
        return v.get_building()->get_owner().get_id() == p.get_id();
    }

    for (ariel::Tile *tile : this->tiles) // Finding all of the tiles that vertex is adjecent to
    {
        if (std::find(tile->get_vertices().begin(), tile->get_vertices().end(), &v) != tile->get_vertices().end()) // If not found, an iterator to the end will be returned.
        {
            for (size_t i = 0; i < VERTICES_PER_TILE; i++)
            {
                if (tile->get_vertices().at(i)->get_id() == v.get_id())
                {

                    // Check if it's neighbour vertex has a village/city of other player
                    if (!tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->is_free() &&
                        tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->get_building()->get_owner().get_id() != p.get_id())
                    {
                        return false;
                    }

                    if (!tile->get_vertices().at(Utils::good_mod(i - 1, VERTICES_PER_TILE))->is_free() &&
                        tile->get_vertices().at(Utils::good_mod(i - 1, VERTICES_PER_TILE))->get_building()->get_owner().get_id() != p.get_id())
                    {
                        return false;
                    }

                    // Check if theres a road to that vertex
                    if (tile->get_edges().at(i)->isTaken() && tile->get_edges().at(i)->get_owner()->get_id() == p.get_id())
                    {
                        return true;
                    }

                    if (tile->get_edges().at(Utils::good_mod(i - 1, EDGES_PER_TILE))->isTaken() &&
                        tile->get_edges().at(Utils::good_mod(i - 1, EDGES_PER_TILE))->get_owner()->get_id() == p.get_id())
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
    for (ariel::Tile *tile : this->tiles)
    {
        if (std::find(tile->get_edges().begin(), tile->get_edges().end(), &e) != tile->get_edges().end()) // If not found, an iterator to the end will be returned.
        {
            for (size_t i = 0; i < EDGES_PER_TILE; i++)
            {
                if (tile->get_edges().at(i)->get_id() == e.get_id())
                {
                    // Check the edge adjecent edges
                    if (tile->get_edges().at(Utils::good_mod(i - 1, EDGES_PER_TILE))->get_owner() == nullptr) // If this place has no road yet
                    {
                        continue;
                    }
                    if (!(tile->get_edges().at(Utils::good_mod(i - 1, EDGES_PER_TILE))->get_owner()->get_id() == p.get_id())) // i - 1 might be a nagative number
                        valid1 = true;

                    if (tile->get_edges().at(Utils::good_mod(i + 1, EDGES_PER_TILE))->get_owner() == nullptr) // If this place has no road yet
                    {
                        continue;
                    }
                    if (!(tile->get_edges().at(Utils::good_mod(i + 1, EDGES_PER_TILE))->get_owner()->get_id() == p.get_id())) // i + 1 might be > EDGES_PER_TILE
                        valid2 = true;

                    // Checking if theres an adjecent village / city
                    if (!tile->get_vertices().at(i)->is_free())
                    {
                        has_village = tile->get_vertices().at(i)->get_building()->get_owner().get_id() == p.get_id();
                    }

                    if (!tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->is_free())
                    {
                        has_village = tile->get_vertices().at(i)->get_building()->get_owner().get_id() == p.get_id();
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

std::vector<ariel::Tile *> ariel::Board::get_tiles()
{
    return this->tiles;
}

std::vector<ariel::Edge *> ariel::Board::get_edges()
{
    return this->edges;
}
