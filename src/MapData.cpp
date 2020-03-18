#include "MapData.hpp"

MapData::MapData(const Rules& rules):
    m_rules         (rules)
{}

void MapData::setCell(const sf::Vector2i& cell, uint8_t id)
{
    get(cell) = id;
}

void MapData::nextIn(const sf::Vector2i& cell)
{
    uint8_t& id = get(cell);
    id = m_rules.getNext(id);
}

uint8_t MapData::getCell(sf::Vector2i cell) const
{
    cell.x -= m_data.second;

    if(cell.x >= 0 && cell.x < static_cast<int>(m_data.first.size()))
    {
        auto temp = &m_data.first[cell.x];

        cell.y -= temp->second;

        if(cell.y >= 0 && cell.y < static_cast<int>(temp->first.size()))
            return temp->first[cell.y];
    }

    return m_rules.defaultId();
}

void MapData::reset()
{
    m_data = std::pair<Dvector<std::pair<Dvector<uint8_t>, int>>, int>();
}

const Rules& MapData::rules()
{
    return m_rules;
}

uint8_t& MapData::get(const sf::Vector2i& cell)
{
    if(cell.x < m_data.second)
    {
        if(m_data.first.empty())
            m_data.second = cell.x + 1;

        for(; cell.x < m_data.second; --m_data.second)
            m_data.first.emplace_front();
    }
    else if(cell.x >= static_cast<int>(m_data.first.size()) + m_data.second)
    {
        if(m_data.first.empty())
            m_data.second = cell.x;

        while(cell.x >= static_cast<int>(m_data.first.size()) + m_data.second)
            m_data.first.emplace_back();
    }

    auto temp = &m_data.first[cell.x - m_data.second];

    if(cell.y < temp->second)
    {
        if(temp->first.empty())
            temp->second = cell.y + 1;

        for(; cell.y < temp->second; --temp->second)
            temp->first.push_front(m_rules.defaultId());
    }
    else if(cell.y >= static_cast<int>(temp->first.size()) + temp->second)
    {
        if(temp->first.empty())
            temp->second = cell.y;

        while(cell.y >= static_cast<int>(temp->first.size()) + temp->second)
            temp->first.push_back(m_rules.defaultId());
    }

    return temp->first[cell.y - temp->second];
}
