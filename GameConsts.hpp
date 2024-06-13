#pragma once
#include <string>

namespace GameConsts
{
    enum class ResourceCard
    {
        Brick,
        Wood,
        Ore,
        Grain,
        Wool
    };
    enum class MapValues
    {
        FOREST,
        HILL,
        MOUNTAIN,
        FIELD,
        PASTURES,
        SEA,
        DESERT
    };
    enum class DevelopmentCard
    {
        KNIGHT,
        MONOPOLY,
        BUILD_ROAD,
        YEAR_OF_PLENTY,
        WINNING_POINTS
    };

    std::string to_string(ResourceCard card);
    std::string to_string(MapValues value);
    std::string to_string(DevelopmentCard card);
};

class Utils
{
public:
    static size_t good_mod(size_t mod, int base);
};