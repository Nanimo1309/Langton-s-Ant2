#include "Ant.hpp"

Ant::Ant():
    m_direction (Direction::Up),
    m_draw      (false)
{}

void Ant::map(Map* map)
{
    m_map = map;
}

void Ant::step()
{
    m_map->nextIn(m_position);

    direction(m_map->rules().getDirection(m_map->getCell(m_position)) + m_direction);

    if(m_direction == Direction::Up)
        ++m_position.y;
    else if(m_direction == Direction::Down)
        --m_position.y;
    else if(m_direction == Direction::Right)
        ++m_position.x;
    else if(m_direction == Direction::Left)
        --m_position.x;
}

void Ant::texture(std::shared_ptr<sf::Texture> texture)
{
    m_draw = true;
    m_texture = texture;
    m_sprite.setTexture(*m_texture, true);
    m_sprite.setOrigin({static_cast<float>(m_texture->getSize().x) * 0.5f, static_cast<float>(m_texture->getSize().y) * 0.5f});
    m_sprite.setScale(1.f / m_texture->getSize().x, 1.f / m_texture->getSize().y);
}

void Ant::position(const sf::Vector2i& position)
{
    m_position = position;
    m_map->setCell(m_position, 0);

    sf::Vector2f draw = static_cast<sf::Vector2f>(m_position);
    draw.y = -draw.y - 0.5f;
    draw.x += 0.5f;
    m_sprite.setPosition(draw);
}

sf::Vector2i Ant::position() const
{
    return m_position;
}

void Ant::direction(Direction direction)
{
    m_direction = direction;
    m_sprite.setRotation(direction);
}

Direction Ant::direction() const
{
    return m_direction;
}

void Ant::speed(double speed)
{
    m_speed = speed;
}

double Ant::speed() const
{
    return m_speed;
}

void Ant::update(double delay)
{
    if(!m_draw)
        return;

    sf::Vector2f position = m_sprite.getPosition(),
                 destiny = static_cast<sf::Vector2f>(m_position);

    destiny.y = -destiny.y - 0.5f;
    destiny.x += 0.5f;

    if(m_speed >= 1000.f)
        m_sprite.setPosition(destiny);

    if(position.x < destiny.x)
    {
        position.x += m_speed * delay;

        if(position.x > destiny.x)
            position.x = destiny.x;
    }
    else if(position.x > destiny.x)
    {
        position.x -= m_speed * delay;

        if(position.x < destiny.x)
            position.x = destiny.x;
    }

    if(position.y < destiny.y)
    {
        position.y += m_speed * delay;

        if(position.y > destiny.y)
            position.y = destiny.y;
    }
    else if(position.y > destiny.y)
    {
        position.y -= m_speed * delay;

        if(position.y < destiny.y)
            position.y = destiny.y;
    }

    m_sprite.setPosition(position.x, position.y);
}

void Ant::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_draw)
        target.draw(m_sprite);
}

