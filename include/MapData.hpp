#ifndef MAPDATA_H
#define MAPDATA_H

#include "Headers.hpp"
#include "Dvector.hpp"
#include "Rules.hpp"

class MapData
{
public:
    MapData(const Rules& rules);
    virtual ~MapData() = default;

    virtual void setCell(const sf::Vector2i& cell, uint8_t id);
    virtual void nextIn(const sf::Vector2i& cell);
    uint8_t getCell(sf::Vector2i cell) const;

    virtual void reset();

    const Rules& rules();

protected:
    const Rules m_rules;

private:
    uint8_t& get(const sf::Vector2i& cell);

    std::pair<Dvector<std::pair<Dvector<uint8_t>, int>>, int> m_data;
};

#endif // MAPDATA_H
