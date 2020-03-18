#ifndef ANT_H
#define ANT_H

#include "Map.hpp"

class Ant:
    public Direction,
    public sf::Drawable
{
public:
    Ant();
    virtual ~Ant() = default;

    void map(Map* map);

    void step();

    void texture(std::shared_ptr<sf::Texture> texture);

    void position(const sf::Vector2i& position);
    sf::Vector2i position() const;

    void direction(Direction direction);
    Direction direction() const;

    void speed(double speed);
    double speed() const;

    void update(double delay);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Map* m_map;
    sf::Vector2i m_position;
    Direction m_direction;

    std::shared_ptr<sf::Texture> m_texture;
    sf::Sprite m_sprite;

    float m_speed;

    bool m_draw;
};

#endif // ANT_H
