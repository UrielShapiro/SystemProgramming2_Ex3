/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#pragma once

#include "Board.hpp"
#include "Buildable.hpp"
#include "GameConsts.hpp"

#define RESOURCES_PER_TILE 3

namespace ariel
{
    class Buildable;
    class Vertex
    {
    private:
        Buildable *building;
        const short ID;
        bool is_taken;
        GameConsts::MapValues resouces[RESOURCES_PER_TILE];

    public:
        Vertex(const GameConsts::MapValues resource1, const GameConsts::MapValues resource2, const GameConsts::MapValues resource3, const short id);
        void set_building(ariel::Buildable *b);
        Buildable *get_building();
        bool is_free() const;
        const GameConsts::MapValues *get_resources() const;
        short get_id() const;
        ~Vertex() =default;
    };
}