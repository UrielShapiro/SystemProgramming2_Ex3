#pragma once

#include "Board.hpp"
#include "Buildable.hpp"

#define RESOURCES_PER_TILE 3

using namespace GameConsts;

namespace ariel
{
    class Vertex
    {
    private:
        Buildable *building;
        const short ID;
        bool is_taken;
        MapValues resouces[RESOURCES_PER_TILE];

    public:
        Vertex(const MapValues resource1, const MapValues resource2, const MapValues resource3, const short id);
        void set_building(ariel::Buildable *b);
        const Buildable *get_building() const;
        const bool is_free() const;
        const MapValues *get_resources() const;
        const short get_id() const;
    };
}