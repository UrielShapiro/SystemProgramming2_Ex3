/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#pragma once
#include "Player.hpp"
#include "Board.hpp"
#include "GameConsts.hpp"

#define MAX_RESOURCES_PER_BUILDABLE 3

namespace ariel
{
    class Player; // Forward declaration

    class Buildable
    {
    protected:
        Player &owner;
        GameConsts::MapValues resources[MAX_RESOURCES_PER_BUILDABLE];
        Buildable(Player &p, const GameConsts::MapValues resources_list[MAX_RESOURCES_PER_BUILDABLE]);

    public:
        Buildable(const Buildable &other);
        virtual std::string get_type() const = 0;
        const GameConsts::MapValues *get_resources() const;
        Player &get_owner();
        virtual ~Buildable() = default;
    };

    class Village : public Buildable
    {
    public:
        Village(Player &p, const GameConsts::MapValues resources_list[MAX_RESOURCES_PER_BUILDABLE]);
        std::string get_type() const override;
    };

    class City : public Buildable
    {
    public:
        City(Player &p, const GameConsts::MapValues resources_list[MAX_RESOURCES_PER_BUILDABLE]);
        std::string get_type() const override;
    };

};
