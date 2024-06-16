/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#include "GameConsts.hpp"

std::string GameConsts::to_string(ResourceCard card)
{
    switch (card)
    {
    case ResourceCard::Brick:
        return "Brick";
    case ResourceCard::Wood:
        return "Wood";
    case ResourceCard::Ore:
        return "Ore";
    case ResourceCard::Grain:
        return "Grain";
    case ResourceCard::Wool:
        return "Wool";
    default:
        return "Unknown";
    }
}

std::string GameConsts::to_string(MapValues value)
{
    switch (value)
    {
    case MapValues::FOREST:
        return "Forest";
    case MapValues::HILL:
        return "Hill";
    case MapValues::MOUNTAIN:
        return "Mountain";
    case MapValues::FIELD:
        return "Field";
    case MapValues::PASTURES:
        return "Pastures";
    case MapValues::SEA:
        return "Sea";
    case MapValues::DESERT:
        return "Desert";
    default:
        return "Unknown";
    }
}

std::string GameConsts::to_string(DevelopmentCard card)
{
    switch (card)
    {
    case DevelopmentCard::KNIGHT:
        return "Knight";
    case DevelopmentCard::MONOPOLY:
        return "Monopoly";
    case DevelopmentCard::BUILD_ROAD:
        return "Build Road";
    case DevelopmentCard::YEAR_OF_PLENTY:
        return "Year of Plenty";
    case DevelopmentCard::WINNING_POINTS:
        return "Winning Points";
    default:
        return "Unknown";
    }
}

// To avoid reaching over the vector boundries or attempting to reach negative cell in the cell
size_t Utils::good_mod(size_t mod, int base)
{
    return ((mod % base) + base) % base;
}
