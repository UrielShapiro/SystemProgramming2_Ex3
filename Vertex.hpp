#pragma once

#include "Board.hpp"
#include "Buildable.hpp"

namespace ariel
{
    class Vertex
    {
    private:
        Buildable *building;
        bool is_taken;
        MapValues resouces[3];

    public:
        Vertex(const MapValues resource[3]);
        void set_building(ariel::Buildable *b);
        const Buildable *get_building() const;
        const bool is_free() const;
        const MapValues *get_resources() const;
    };
}