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
}