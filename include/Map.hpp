#ifndef MAP_HPP
#define MAP_HPP

#include "MapData.hpp"

class Map:
    public MapData,
    public sf::Drawable
{
public:
    Map(const Rules& rules);
    virtual ~Map() = default;

    virtual void setCell(const sf::Vector2i& cell, uint8_t id) override;
    virtual void nextIn(const sf::Vector2i& cell) override;

    virtual void reset() override;

    void display();

    sf::Vector2u size() const;
    sf::Vector2u center() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void drawCell(const sf::Vector2i& cell);

    void checkTexture(const size_t& index, sf::Vector2u size);

    sf::VertexArray m_buffer[4];

    sf::Texture m_texture[4];
    sf::Sprite m_sprite[4];

    sf::Vector2u m_size;
    sf::Vector2u m_center;
};

#endif // MAP_HPP
