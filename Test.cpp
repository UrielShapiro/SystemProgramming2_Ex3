/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Catan.hpp"

TEST_CASE("Player Class")
{
    SUBCASE("Player Constructor")
    {
        ariel::Player p1("Amit");
        CHECK_EQ(p1.get_name(), "Amit");
        CHECK_EQ(p1.get_development_cards().size(), 0);
        CHECK_EQ(p1.get_victory_points(), 0);
        CHECK_EQ(p1.get_total_cards(), 0);
        CHECK_EQ(p1.get_id(), 0);

        ariel::Player p2("Dana");
        CHECK_EQ(p2.get_name(), "Dana");
        CHECK_EQ(p2.get_development_cards().size(), 0);
        CHECK_EQ(p2.get_victory_points(), 0);
        CHECK_EQ(p2.get_total_cards(), 0);
        CHECK_EQ(p2.get_id(), 1);
    }

    SUBCASE("Player change_victory_points")
    {
        ariel::Player p1("Amit");
        p1.change_victory_points(1);
        CHECK_EQ(p1.get_victory_points(), 1);
        p1.change_victory_points(-1);
        CHECK_EQ(p1.get_victory_points(), 0);
        CHECK_THROWS(p1.change_victory_points(-1));
        CHECK_THROWS(p1.change_victory_points(100));
    }

    SUBCASE("Player change_resource_amount - MapValues")
    {
        ariel::Player p1("Dana");
        p1.change_resource_amount(GameConsts::MapValues::FOREST, 1);
        CHECK_EQ(p1.get_total_cards(), 1);
        p1.change_resource_amount(GameConsts::MapValues::PASTURES, 1);
        CHECK_EQ(p1.get_total_cards(), 2);
        p1.change_resource_amount(GameConsts::MapValues::FOREST, -1);
        CHECK_EQ(p1.get_total_cards(), 1);
        CHECK_THROWS(p1.change_resource_amount(GameConsts::MapValues::FOREST, -2));
        CHECK_THROWS(p1.change_resource_amount(GameConsts::MapValues::MOUNTAIN, -100));
        CHECK_THROWS_AS(p1.change_resource_amount(GameConsts::MapValues::MOUNTAIN, -100), std::runtime_error);
    }

    SUBCASE("Player change_resource_amount - MapValues array")
    {
        ariel::Player p1("Yossi");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::SEA};
        p1.change_resource_amount(resources, 1);
        CHECK_EQ(p1.get_total_cards(), 1);
        GameConsts::MapValues resources2[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::HILL, GameConsts::MapValues::PASTURES};
        p1.change_resource_amount(resources2, 1);
        CHECK_EQ(p1.get_total_cards(), 4);
        p1.change_resource_amount(resources2, -1);
        CHECK_EQ(p1.get_total_cards(), 1);
        CHECK_THROWS(p1.change_resource_amount(resources, -2));
        CHECK_THROWS(p1.change_resource_amount(resources, -100));
        CHECK_THROWS_AS(p1.change_resource_amount(resources, -100), std::runtime_error);
    }

    SUBCASE("Player change_resource_amount - ResourceCard")
    {
        ariel::Player p1("Dana");
        p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        CHECK_EQ(p1.get_total_cards(), 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Ore, 1);
        CHECK_EQ(p1.get_total_cards(), 2);
        p1.change_resource_amount(GameConsts::ResourceCard::Brick, -1);
        CHECK_EQ(p1.get_total_cards(), 1);
        CHECK_THROWS(p1.change_resource_amount(GameConsts::ResourceCard::Grain, -2));
        CHECK_THROWS_AS(p1.change_resource_amount(GameConsts::ResourceCard::Brick, -100), std::runtime_error);
    }

    SUBCASE("Player change_victory_points + get_victory_points")
    {
        ariel::Player p1("Dana");
        p1.change_victory_points(1);
        CHECK_EQ(p1.get_victory_points(), 1);
        p1.change_victory_points(-1);
        CHECK_EQ(p1.get_victory_points(), 0);
        CHECK_THROWS(p1.change_victory_points(-1));  // < 0
        CHECK_THROWS(p1.change_victory_points(100)); // > 2
    }

    SUBCASE("Player placeRoad")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        std::vector<size_t> edge_placement = {1, 6};
        std::vector<size_t> vertex_placement = {0, 1};
        p1.game_start_placement(*(catan.getBoard()), edge_placement, vertex_placement);

        // Give the player resources to build a road
        p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wood, 1);

        ariel::Edge *e = catan.getBoard()->get_edges()[2];

        p1.placeRoad(*(catan.getBoard()), *e);
        CHECK_EQ(e->get_owner(), &p1);
        CHECK(e->isTaken());
        CHECK_THROWS(p1.placeRoad(*(catan.getBoard()), *e)); // Already taken

        ariel::Edge *e2 = catan.getBoard()->get_edges()[3];
        CHECK_THROWS(p2.placeRoad(*(catan.getBoard()), *e2)); // Not enough resources
    }

    SUBCASE("Player set_largest_army")
    {
        ariel::Player p1("Dana");
        CHECK_FALSE(p1.get_is_largest_army());
        p1.set_largest_army(true);
        CHECK(p1.get_is_largest_army());
        p1.set_largest_army(true); // Already has the largest army
        CHECK(p1.get_is_largest_army());
        p1.set_largest_army(false);
        CHECK_FALSE(p1.get_is_largest_army());
        p1.set_largest_army(false); // Already doesn't have the largest army
        CHECK_FALSE(p1.get_is_largest_army());
    }

    SUBCASE("Player game_start_placement")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        std::vector<size_t> edge_placement = {1, 6};
        std::vector<size_t> vertex_placement = {0, 1};
        p1.game_start_placement(*(catan.getBoard()), edge_placement, vertex_placement);

        CHECK(catan.getBoard()->get_edges()[1]->isTaken());
        CHECK(catan.getBoard()->get_edges()[6]->isTaken());

        CHECK_EQ(catan.getBoard()->get_edges()[1]->get_owner()->get_id(), p1.get_id());
        CHECK_EQ(catan.getBoard()->get_edges()[6]->get_owner()->get_id(), p1.get_id());

        CHECK_FALSE(catan.getBoard()->get_vertices()[1]->is_free());
        CHECK_FALSE(catan.getBoard()->get_vertices()[6]->is_free());

        CHECK_EQ(catan.getBoard()->get_vertices()[1]->get_building()->get_owner().get_id(), p1.get_id());
        CHECK_EQ(catan.getBoard()->get_vertices()[6]->get_building()->get_owner().get_id(), p1.get_id());

        CHECK_THROWS(p1.game_start_placement(*(catan.getBoard()), edge_placement, vertex_placement)); // Already placed
        CHECK_THROWS(p2.game_start_placement(*(catan.getBoard()), edge_placement, vertex_placement));
    }

    SUBCASE("Player Trade - ResourceCard")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        // Fill the players with resources
        p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Ore, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Grain, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wool, 1);

        p2.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p2.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
        p2.change_resource_amount(GameConsts::ResourceCard::Ore, 1);
        p2.change_resource_amount(GameConsts::ResourceCard::Grain, 1);
        p2.change_resource_amount(GameConsts::ResourceCard::Wool, 1);

        p3.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p3.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
        p3.change_resource_amount(GameConsts::ResourceCard::Ore, 1);
        p3.change_resource_amount(GameConsts::ResourceCard::Grain, 1);
        p3.change_resource_amount(GameConsts::ResourceCard::Wool, 1);

        std::vector<GameConsts::ResourceCard> vec = {GameConsts::ResourceCard::Brick, GameConsts::ResourceCard::Wood};
        CHECK(p1.trade(p2, vec));
        CHECK_EQ(p1.get_total_cards(), 7); // 5 + 2
        CHECK_EQ(p2.get_total_cards(), 3); // 5 - 2

        std::vector<GameConsts::ResourceCard> vec2 = {GameConsts::ResourceCard::Brick, GameConsts::ResourceCard::Wood};
        CHECK_FALSE(p1.trade(p2, vec2)); // Not enough resources
        CHECK_EQ(p1.get_total_cards(), 7);
        CHECK_EQ(p2.get_total_cards(), 3);

        std::vector<GameConsts::ResourceCard> vec3 = {GameConsts::ResourceCard::Wool, GameConsts::ResourceCard::Wood};
        CHECK(p2.trade(p3, vec3));
        CHECK_EQ(p2.get_total_cards(), 5);
        CHECK_EQ(p3.get_total_cards(), 3);
    }

    SUBCASE("Player Trade - DevelopmentCards")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        // Fill the players with development cards
        p1.add_development_card(GameConsts::DevelopmentCard::KNIGHT);
        p1.add_development_card(GameConsts::DevelopmentCard::BUILD_ROAD);
        p1.add_development_card(GameConsts::DevelopmentCard::MONOPOLY);
        p1.add_development_card(GameConsts::DevelopmentCard::KNIGHT);

        p2.add_development_card(GameConsts::DevelopmentCard::KNIGHT);
        p2.add_development_card(GameConsts::DevelopmentCard::KNIGHT);
        p2.add_development_card(GameConsts::DevelopmentCard::KNIGHT);

        CHECK(p1.trade(p2, p2.get_development_cards()));
        CHECK_EQ(p1.get_development_cards().size(), 7); // 4 + 3

        std::vector<GameConsts::DevelopmentCard> vec = {GameConsts::DevelopmentCard::KNIGHT,
                                                        GameConsts::DevelopmentCard::BUILD_ROAD};
        CHECK_FALSE(p1.trade(p2, vec)); // Not enough resources
        CHECK_EQ(p1.get_development_cards().size(), 7);
        CHECK(p3.trade(p1, vec));
        CHECK_EQ(p3.get_development_cards().size(), 2);
    }

    SUBCASE("Player Discard Half Cards")
    {
        ariel::Player p1("Dana");

        p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Ore, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Grain, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wool, 1);

        p1.discard_half_cards();
        CHECK_EQ(p1.get_total_cards(), 5); // Does nothing when the total cards is <= 7

        for (int i = 0; i < 10; i++)
        {
            p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        }

        p1.discard_half_cards();
        CHECK_EQ(p1.get_total_cards(), 7); // 15 / 2 = 7
    }
}

TEST_CASE("Vertex Class")
{
    SUBCASE("Vertex Constructor")
    {
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::SEA};
        ariel::Vertex v(resources[0], resources[1], resources[2], 1);
        CHECK_EQ(v.get_id(), 1);
        CHECK_EQ(v.get_resources()[0], GameConsts::MapValues::FOREST);
        CHECK_EQ(v.get_resources()[1], GameConsts::MapValues::DESERT);
        CHECK_EQ(v.get_resources()[2], GameConsts::MapValues::SEA);
        CHECK_EQ(v.get_building(), nullptr);
        CHECK(v.is_free());
    }

    SUBCASE("Vertex set_building + get_building")
    {
        ariel::Player p1("Uriel");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST,
                                             GameConsts::MapValues::DESERT,
                                             GameConsts::MapValues::SEA};
        ariel::Vertex v(resources[0], resources[1], resources[2], 1);
        ariel::Village b(p1, resources);
        v.set_building(&b);
        CHECK_EQ(v.get_building(), &b);
        CHECK_FALSE(v.is_free());
        CHECK_EQ(v.get_building()->get_owner().get_id(), p1.get_id());
    }

    SUBCASE("Vertex is_free")
    {
        GameConsts::MapValues resources1[] = {GameConsts::MapValues::FOREST,
                                              GameConsts::MapValues::DESERT,
                                              GameConsts::MapValues::SEA};
        ariel::Vertex v1(resources1[0], resources1[1], resources1[2], 0);
        CHECK(v1.is_free()); // Is free

        ariel::Player p1("Uriel");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST,
                                             GameConsts::MapValues::DESERT,
                                             GameConsts::MapValues::SEA};
        ariel::Vertex v(resources[0], resources[1], resources[2], 1);
        ariel::Village b(p1, resources);
        v.set_building(&b);
        CHECK_FALSE(v.is_free()); // Is not free
    }

    SUBCASE("Vertex get_resources")
    {
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST,
                                             GameConsts::MapValues::DESERT,
                                             GameConsts::MapValues::SEA};
        ariel::Vertex v(resources[0], resources[1], resources[2], 1);
        CHECK_EQ(v.get_resources()[0], GameConsts::MapValues::FOREST);
        CHECK_EQ(v.get_resources()[1], GameConsts::MapValues::DESERT);
        CHECK_EQ(v.get_resources()[2], GameConsts::MapValues::SEA);
    }

    SUBCASE("Vertex get_id")
    {
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST,
                                             GameConsts::MapValues::DESERT,
                                             GameConsts::MapValues::SEA};
        ariel::Vertex v(resources[0], resources[1], resources[2], 20);
        CHECK_EQ(v.get_id(), 20);
    }
}

TEST_CASE("Tile Class")
{
    SUBCASE("Tile Constructor")
    {
        ariel::Edge *e[6];
        ariel::Vertex *v[6];
        std::vector<GameConsts::MapValues> resources = {GameConsts::MapValues::FOREST,
                                                        GameConsts::MapValues::DESERT,
                                                        GameConsts::MapValues::SEA};
        for (int i = 0; i < EDGES_PER_TILE; i++)
        {
            e[i] = new ariel::Edge(i);
            v[i] = new ariel::Vertex(resources[0], resources[1], resources[2], i);
        }

        ariel::Tile t(1, 1, GameConsts::MapValues::FOREST, e, v);
        CHECK_EQ(t.get_ID(), 1);
        CHECK_EQ(t.get_token(), 1);
        CHECK_EQ(t.get_value(), GameConsts::MapValues::FOREST);
        CHECK_EQ(t.get_edges().size(), EDGES_PER_TILE);
        CHECK_EQ(t.get_vertices().size(), VERTICES_PER_TILE);

        for (int i = 0; i < EDGES_PER_TILE; i++)
        {
            delete e[i];
            delete v[i];
        }
    }

    SUBCASE("Tile get_edges")
    {
        ariel::Edge *e[6];
        ariel::Vertex *v[6];
        std::vector<GameConsts::MapValues> resources = {GameConsts::MapValues::FOREST,
                                                        GameConsts::MapValues::DESERT,
                                                        GameConsts::MapValues::SEA};
        for (int i = 0; i < EDGES_PER_TILE; i++)
        {
            e[i] = new ariel::Edge(i);
            v[i] = new ariel::Vertex(resources[0], resources[1], resources[2], i);
        }

        ariel::Tile t(1, 1, GameConsts::MapValues::FOREST, e, v);
        CHECK_EQ(t.get_edges().size(), EDGES_PER_TILE);
        CHECK_EQ(t.get_edges()[0], e[0]);
        CHECK_EQ(t.get_edges()[1], e[1]);
        CHECK_EQ(t.get_edges()[2], e[2]);
        CHECK_EQ(t.get_edges()[3], e[3]);
        CHECK_EQ(t.get_edges()[4], e[4]);
        CHECK_EQ(t.get_edges()[5], e[5]);

        for (int i = 0; i < EDGES_PER_TILE; i++)
        {
            delete e[i];
            delete v[i];
        }
    }

    SUBCASE("Tile get_vertices")
    {
        ariel::Edge *e[6];
        ariel::Vertex *v[6];
        std::vector<GameConsts::MapValues> resources = {GameConsts::MapValues::FOREST,
                                                        GameConsts::MapValues::DESERT,
                                                        GameConsts::MapValues::SEA};
        for (int i = 0; i < VERTICES_PER_TILE; i++)
        {
            e[i] = new ariel::Edge(i);
            v[i] = new ariel::Vertex(resources[0], resources[1], resources[2], i);
        }

        ariel::Tile t(1, 1, GameConsts::MapValues::FOREST, e, v);
        CHECK_EQ(t.get_vertices().size(), 6);
        CHECK_EQ(t.get_vertices()[0], v[0]);
        CHECK_EQ(t.get_vertices()[1], v[1]);
        CHECK_EQ(t.get_vertices()[2], v[2]);
        CHECK_EQ(t.get_vertices()[3], v[3]);
        CHECK_EQ(t.get_vertices()[4], v[4]);
        CHECK_EQ(t.get_vertices()[5], v[5]);

        for (int i = 0; i < VERTICES_PER_TILE; i++)
        {
            delete e[i];
            delete v[i];
        }
    }

    SUBCASE("Tile get_value")
    {
        ariel::Edge *e[6];
        ariel::Vertex *v[6];
        std::vector<GameConsts::MapValues> resources = {GameConsts::MapValues::FOREST,
                                                        GameConsts::MapValues::DESERT,
                                                        GameConsts::MapValues::SEA};
        for (int i = 0; i < VERTICES_PER_TILE; i++)
        {
            e[i] = new ariel::Edge(i);
            v[i] = new ariel::Vertex(resources[0], resources[1], resources[2], i);
        }

        ariel::Tile t(1, 1, GameConsts::MapValues::FOREST, e, v);
        CHECK_EQ(t.get_value(), GameConsts::MapValues::FOREST);

        ariel::Tile t2(1, 1, GameConsts::MapValues::MOUNTAIN, e, v);
        CHECK_EQ(t2.get_value(), GameConsts::MapValues::MOUNTAIN);

        ariel::Tile t3(1, 1, GameConsts::MapValues::HILL, e, v);
        CHECK_EQ(t3.get_value(), GameConsts::MapValues::HILL);

        for (int i = 0; i < VERTICES_PER_TILE; i++)
        {
            delete e[i];
            delete v[i];
        }
    }
}

TEST_CASE("Edge Class")
{
    SUBCASE("Edge Constructor")
    {
        ariel::Edge e(1);
        CHECK_EQ(e.get_id(), 1);
        CHECK_EQ(e.get_owner(), nullptr);
        CHECK_FALSE(e.isTaken());
    }

    SUBCASE("Edge set_road + get_owner")
    {
        ariel::Player p1("Uriel");
        ariel::Edge e(1);
        e.set_road(p1);
        CHECK_EQ(e.get_owner(), &p1);

        ariel::Player p2("Dana");
        CHECK_NE(e.get_owner(), &p2); // Check not equal
    }

    SUBCASE("Edge isTaken")
    {
        ariel::Player p1("Uriel");
        ariel::Edge e(1);
        CHECK_FALSE(e.isTaken());
        e.set_road(p1);
        CHECK(e.isTaken());
    }

    SUBCASE("Edge get_id")
    {
        ariel::Edge e(1);
        CHECK_EQ(e.get_id(), 1);
    }
}

TEST_CASE("Catan Class")
{
    SUBCASE("Catan constructor")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        CHECK_EQ(catan.get_players()[0].get_name(), "Dana");
        CHECK_EQ(catan.get_players()[1].get_name(), "Yossi");
        CHECK_EQ(catan.get_players()[2].get_name(), "Amit");
        CHECK_EQ(catan.getBoard()->get_tiles().size(), NUM_OF_TILES);
        CHECK_EQ(catan.getBoard()->get_edges().size(), NUM_OF_EDGES);
        CHECK_EQ(catan.getBoard()->get_vertices().size(), NUM_OF_VERTICES);
        CHECK_EQ(catan.getBoard()->get_tiles()[0]->get_ID(), 0);
        CHECK_EQ(catan.getBoard()->get_edges()[0]->get_id(), 0);
        CHECK_EQ(catan.getBoard()->get_vertices()[0]->get_id(), 0);
    }

    SUBCASE("Catan StartingGame")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        std::vector<size_t> edge_placement = {1, 6, 12, 18, 60, 52};
        std::vector<size_t> vertex_placement = {0, 1, 0, 1, 0, 1};
        catan.StartingGame(edge_placement, vertex_placement);

        CHECK(catan.getBoard()->get_edges()[1]->isTaken());
        CHECK(catan.getBoard()->get_edges()[6]->isTaken());

        CHECK_FALSE(catan.getBoard()->get_vertices()[1]->is_free());
        CHECK_FALSE(catan.getBoard()->get_vertices()[6]->is_free());

        CHECK_EQ(catan.getBoard()->get_vertices()[1]->get_building()->get_owner().get_id(), p1.get_id());
        CHECK_EQ(catan.getBoard()->get_vertices()[6]->get_building()->get_owner().get_id(), p1.get_id());

        CHECK_THROWS(catan.StartingGame(edge_placement, vertex_placement)); // Already placed
    }

    SUBCASE("Catan rollDice")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);
        for (int i = 0; i < 20; i++)
        {
            CHECK(catan.rollDice() < 13);
            CHECK(catan.rollDice() > 1);
        }
    }

    SUBCASE("Catan check_winner")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        CHECK_FALSE(catan.check_winner());
        for (int i = 0; i < 4; i++)
        {
            catan.get_players()[0].change_victory_points(2);
            CHECK_FALSE(catan.check_winner());
        }
        catan.get_players()[0].change_victory_points(2);
        CHECK(catan.check_winner());
    }

    SUBCASE("Catan check_largest_army")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        CHECK_FALSE(catan.check_largest_army());
        for (int i = 0; i < INITIATE_LARGEST_ARMY - 1; i++)
        {
            catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::KNIGHT);
            CHECK_FALSE(catan.check_largest_army());
        }
        catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::KNIGHT);
        CHECK(catan.check_largest_army());
    }

    SUBCASE("Catan buyDevelopmentCard")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        // Give the player resources to buy a development card
        p1.change_resource_amount(GameConsts::ResourceCard::Ore, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Grain, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wool, 1);

        catan.buyDevelopmentCard(p1);
        CHECK_EQ(p1.get_development_cards().size(), 1);
        CHECK_EQ(p1.get_total_cards(), 0);          // development cards are not counted as resource cards
        CHECK_THROWS(catan.buyDevelopmentCard(p1)); // Not enough resources
    }

    SUBCASE("Catan use_development_card")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::YEAR_OF_PLENTY);
        catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::MONOPOLY);
        catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::BUILD_ROAD);
        catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::WINNING_POINTS);

        CHECK_THROWS(catan.use_development_card(catan.get_players()[1], GameConsts::DevelopmentCard::KNIGHT)); // Not the player turn

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < MAX_NUM_OF_PLAYERS; j++)
            {
                catan.get_players()[j].change_resource_amount(GameConsts::ResourceCard::Brick, 1);
                catan.get_players()[j].change_resource_amount(GameConsts::ResourceCard::Wood, 1);
                catan.get_players()[j].change_resource_amount(GameConsts::ResourceCard::Ore, 1);
                catan.get_players()[j].change_resource_amount(GameConsts::ResourceCard::Grain, 1);
                catan.get_players()[j].change_resource_amount(GameConsts::ResourceCard::Wool, 1);
            }
        }
        SUBCASE("Monopoly Card")
        {
            size_t current_amount = catan.get_players()[0].get_total_cards();
            std::istringstream stream("wood\n");
            std::cin.rdbuf(stream.rdbuf());
            catan.use_development_card(catan.get_players()[0], GameConsts::DevelopmentCard::MONOPOLY);
            CHECK_EQ(catan.get_players()[0].get_total_cards(), current_amount + 10 * (MAX_NUM_OF_PLAYERS - 1));
            std::cin.rdbuf(std::cin.rdbuf()); // Reset cin
        }

        SUBCASE("Year of Plenty Card")
        {
            size_t current_amount1 = catan.get_players()[0].get_total_cards();
            std::istringstream stream("wood Ore\n");
            std::cin.rdbuf(stream.rdbuf()); // Redirect cin to the stream
            catan.use_development_card(catan.get_players()[0], GameConsts::DevelopmentCard::YEAR_OF_PLENTY);
            CHECK_EQ(catan.get_players()[0].get_total_cards(), current_amount1 + 2);
            std::cin.rdbuf(std::cin.rdbuf()); // Reset cin
        }

        SUBCASE("Build Road Card")
        {

            std::vector<size_t> edge_placement = {1, 6};
            std::vector<size_t> vertex_placement = {0, 1};
            catan.get_players()[0].game_start_placement(*(catan.getBoard()), edge_placement, vertex_placement);
            size_t current_amount2 = catan.get_players()[0].get_development_cards().size();

            std::istringstream stream("2 10\n");
            std::cin.rdbuf(stream.rdbuf()); // Redirect cin to the stream

            catan.use_development_card(catan.get_players()[0], GameConsts::DevelopmentCard::BUILD_ROAD);
            CHECK_EQ(catan.get_players()[0].get_development_cards().size(), current_amount2 - 1);

            // Check that the roads were built
            CHECK(catan.getBoard()->get_edges()[2]->isTaken());
            CHECK_EQ(catan.getBoard()->get_edges()[2]->get_owner()->get_id(), catan.get_players()[0].get_id());
            CHECK(catan.getBoard()->get_edges()[10]->isTaken());
            CHECK_EQ(catan.getBoard()->get_edges()[10]->get_owner()->get_id(), catan.get_players()[0].get_id());

            std::cin.rdbuf(std::cin.rdbuf()); // Reset cin
        }

        SUBCASE("Winning Points Card")
        {
            size_t current_amount3 = catan.get_players()[0].get_victory_points();
            catan.use_development_card(catan.get_players()[0], GameConsts::DevelopmentCard::WINNING_POINTS);
            CHECK_EQ(catan.get_players()[0].get_victory_points(), current_amount3 + 1);

            CHECK_THROWS(catan.use_development_card(catan.get_players()[0], GameConsts::DevelopmentCard::WINNING_POINTS)); // Already used
        }

        SUBCASE("Knight Card")
        {
            catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::KNIGHT);
            catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::KNIGHT);
            catan.get_players()[0].add_development_card(GameConsts::DevelopmentCard::KNIGHT);

            catan.use_development_card(catan.get_players()[0], GameConsts::DevelopmentCard::KNIGHT);

            CHECK(catan.get_players()[0].get_is_largest_army());
        }
    }

    SUBCASE("Catan get_players")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        CHECK_EQ(catan.get_players()[0].get_name(), "Dana");
        CHECK_EQ(catan.get_players()[1].get_name(), "Yossi");
        CHECK_EQ(catan.get_players()[2].get_name(), "Amit");
    }
}

TEST_CASE("Board Class")
{
    ariel::Board *b = ariel::Board::get_instance();

    SUBCASE("Board Constructor")
    {
        CHECK_EQ(b->get_tiles().size(), NUM_OF_TILES);
        CHECK_EQ(b->get_edges().size(), NUM_OF_EDGES);
        CHECK_EQ(b->get_vertices().size(), NUM_OF_VERTICES);
    }

    SUBCASE("Board get_instance")
    {
        ariel::Board *b2 = ariel::Board::get_instance();
        CHECK_EQ(b, b2);
    }

    SUBCASE("Board valid_settlement_placement")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        std::vector<size_t> edge_placement = {1, 6, 12, 18, 60, 52};
        std::vector<size_t> vertex_placement = {0, 1, 0, 1, 0, 1};
        catan.StartingGame(edge_placement, vertex_placement);
        CHECK_FALSE(b->valid_settlement_placement(*(b->get_vertices()[0]), (catan.get_players()[0]))); // Already taken

        p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
        p1.placeRoad(*b, *(b->get_edges()[2]));
        CHECK(b->valid_settlement_placement(*(b->get_vertices()[3]), (catan.get_players()[0])));
    }

    SUBCASE("Board valid_road_placement")
    {
        ariel::Player p1("Dana");
        ariel::Player p2("Yossi");
        ariel::Player p3("Amit");
        ariel::Catan catan(p1, p2, p3);

        std::vector<size_t> edge_placement = {1, 6, 12, 18, 60, 52};
        std::vector<size_t> vertex_placement = {0, 1, 0, 1, 0, 1};
        catan.StartingGame(edge_placement, vertex_placement);

        // Give the player resources to build a road
        p1.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
        p1.change_resource_amount(GameConsts::ResourceCard::Wood, 1);

        ariel::Edge *e = b->get_edges()[2];
        CHECK(b->valid_road_placement(*e, p1));
        p1.placeRoad(*b, *e);

        ariel::Edge *e2 = b->get_edges()[28];
        CHECK_FALSE(b->valid_road_placement(*e2, p2)); // Other player
    }

    SUBCASE("Board get_tiles")
    {
        CHECK_EQ(b->get_tiles().size(), NUM_OF_TILES);
        for (int i = 0; i < NUM_OF_TILES; i++)
        {
            CHECK_EQ(b->get_tiles()[i]->get_ID(), i);
        }
    }

    SUBCASE("Board get_edges")
    {
        CHECK_EQ(b->get_edges().size(), NUM_OF_EDGES);
        for (int i = 0; i < NUM_OF_EDGES; i++)
        {
            CHECK_EQ(b->get_edges()[i]->get_id(), i);
        }
    }

    SUBCASE("Board get_vertices")
    {
        CHECK_EQ(b->get_vertices().size(), NUM_OF_VERTICES);
        for (int i = 0; i < NUM_OF_VERTICES; i++)
        {
            CHECK_EQ(b->get_vertices()[i]->get_id(), i);
        }
    }
}

TEST_CASE("Buildable Class")
{
    SUBCASE("Buildable get_resources")
    {
        ariel::Player p1("Dana");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::SEA};
        ariel::Village b(p1, resources);
        CHECK_EQ(b.get_resources()[0], GameConsts::MapValues::FOREST);
        CHECK_EQ(b.get_resources()[1], GameConsts::MapValues::DESERT);
        CHECK_EQ(b.get_resources()[2], GameConsts::MapValues::SEA);

        ariel::City b2(p1, resources);
        CHECK_EQ(b2.get_resources()[0], GameConsts::MapValues::FOREST);
        CHECK_EQ(b2.get_resources()[1], GameConsts::MapValues::DESERT);
        CHECK_EQ(b2.get_resources()[2], GameConsts::MapValues::SEA);
    }

    SUBCASE("Buildable get_owner")
    {
        ariel::Player p1("Dana");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::SEA};
        ariel::Village b(p1, resources);
        CHECK_EQ(b.get_owner().get_id(), p1.get_id());

        ariel::City b2(p1, resources);
        CHECK_EQ(b2.get_owner().get_id(), p1.get_id());
    }

    SUBCASE("Village get_type")
    {
        ariel::Player p1("Dana");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::SEA};
        ariel::Village b(p1, resources);
        CHECK_EQ(b.get_type(), "Village");
    }

    SUBCASE("City get_type")
    {
        ariel::Player p1("Dana");
        GameConsts::MapValues resources[] = {GameConsts::MapValues::FOREST, GameConsts::MapValues::DESERT, GameConsts::MapValues::SEA};
        ariel::City b(p1, resources);
        CHECK_EQ(b.get_type(), "City");
    }
}
