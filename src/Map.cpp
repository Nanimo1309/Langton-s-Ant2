#include "Map.hpp"

Map::Map(const Rules& rules):
    MapData     (rules),
    m_buffer    {sf::VertexArray(sf::Points), sf::VertexArray(sf::Points), sf::VertexArray(sf::Points), sf::VertexArray(sf::Points)}
{
    m_sprite[0].setRotation(Direction::Left);
    m_sprite[1].setRotation(Direction::Down);
    m_sprite[2].setRotation(Direction::Right);
    m_sprite[3].setRotation(Direction::Up);
}

void Map::setCell(const sf::Vector2i& cell, uint8_t id)
{
    MapData::setCell(cell, id);
    drawCell(cell);
}

void Map::nextIn(const sf::Vector2i& cell)
{
    MapData::nextIn(cell);
    drawCell(cell);
}

void Map::reset()
{
    MapData::reset();

    for(size_t i = 0u; i < 4u; ++i)
    {
        m_buffer[i] = sf::VertexArray();
        m_texture[i] = sf::Texture();
        m_sprite[i].setTexture(m_texture[i], true);
    }

    m_size = {};
    m_center = {};
}

void Map::display()
{
    sf::FloatRect bounds;
    sf::RenderTexture target;

    for(size_t i = 0u; i < 4u; ++i)
    {
        if(!m_buffer[i].getVertexCount())
            continue;

        bounds = m_buffer[i].getBounds();
        bounds.left -= 0.5f;
        bounds.top -= 0.5f;
        ++bounds.width;
        ++bounds.height;

        checkTexture(i, {static_cast<uint32_t>(bounds.left + bounds.width), static_cast<uint32_t>(bounds.top + bounds.height)});

        target.create(bounds.width, bounds.height);
        target.setView(sf::View(bounds));

        sf::Sprite sprite;
        sprite.setTexture(m_texture[i]);
        target.draw(sprite);

        target.draw(m_buffer[i]);
        target.display();

        m_buffer[i].clear();

        m_texture[i].update(target.getTexture(), static_cast<uint32_t>(bounds.left), static_cast<uint32_t>(bounds.top));
        m_sprite[i].setTexture(m_texture[i], true);
    }

    sf::Vector2u tex3 = m_texture[3].getSize();

    m_size = {std::max(m_texture[0].getSize().y, tex3.x) + m_center.x, std::max(m_texture[2].getSize().x, tex3.y) + m_center.y};
}

sf::Vector2u Map::size() const
{
    return m_size;
}

sf::Vector2u Map::center() const
{
    return m_center;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(size_t i = 0u; i < 4u; ++i)
        target.draw(m_sprite[i]);
}

void Map::drawCell(const sf::Vector2i& cell)
{
    if(cell.x >= 0)
    {
        if(cell.y >= 0)
            m_buffer[0].append({{static_cast<float>(cell.y) + 0.5f, static_cast<float>(cell.x) + 0.5f}, m_rules.getColor(getCell(cell))});
        else
            m_buffer[3].append({{static_cast<float>(cell.x) + 0.5f, static_cast<float>(-cell.y) - 0.5f}, m_rules.getColor(getCell(cell))});
    }
    else
    {
        if(cell.y >= 0)
            m_buffer[1].append({{static_cast<float>(-cell.x) - 0.5f, static_cast<float>(cell.y) + 0.5f}, m_rules.getColor(getCell(cell))});
        else
            m_buffer[2].append({{static_cast<float>(-cell.y) - 0.5f, static_cast<float>(-cell.x) - 0.5f}, m_rules.getColor(getCell(cell))});
    }
}

void Map::checkTexture(const size_t& index, sf::Vector2u size)
{
    const sf::Vector2u& texSize = m_texture[index].getSize();

    if(texSize.x >= size.x && texSize.y >= size.y)
        return;

    size.x = std::max(size.x, texSize.x);
    size.y = std::max(size.y, texSize.y);

    if(texSize != sf::Vector2u())
    {
        sf::Image mask;
        sf::Texture temp;
        temp.create(size.x, size.y);

        if(size.x - texSize.x)
        {
            mask.create(size.x - texSize.x, size.y, {0, 0, 0, 0});
            temp.update(mask, texSize.x, 0);
        }

        if(size.y - texSize.y)
        {
            mask.create(texSize.x, size.y - texSize.y, {0, 0, 0, 0});
            temp.update(mask, 0, texSize.y);
        }

        temp.update(m_texture[index]);

        m_texture[index] = temp;
    }
    else
    {
        sf::Image mask;
        mask.create(size.x, size.y, {0, 0, 0, 0});

        m_texture[index].loadFromImage(mask);
    }

    m_sprite[index].setTexture(m_texture[index], true);

    if(index != 3)
    {
        sf::Vector2u tex = m_texture[index].getSize();

        switch(index)
        {
        case 0:
            m_center.y = std::max(tex.x, m_center.y);
            break;
        case 1:
            m_center.x = std::max(tex.x, m_center.x);
            m_center.y = std::max(tex.y, m_center.y);
            break;
        case 2:
            m_center.x = std::max(tex.y, m_center.x);
            break;
        }
    }
}

