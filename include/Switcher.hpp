#ifndef SWITCHER_H
#define SWITCHER_H

#include "Button.hpp"

class Switcher:
    public sf::Drawable
{
public:
    Switcher();
    Switcher(const Switcher& switcher);
    virtual ~Switcher() = default;

    Switcher& operator=(const Switcher& switcher);

    bool check(const sf::Event& event);

    void addButton(std::shared_ptr<Button> button);

    void activate(size_t index);
    size_t active();

    void texture(std::shared_ptr<sf::Texture> texture);

    void position(sf::Vector2f pos);
    void size(sf::Vector2f siz);

    void color(const sf::Color& color);
    void hoverColor(const sf::Color& color);
    void activeColor(const sf::Color& color);

    void textColor(const sf::Color& color);
    void textOutlineColor(const sf::Color& color);
    void textOutlineThickness(const float& size);

    void textFont(const sf::Font& font);
    void textSet(const sf::String& text, size_t index);
    void textSize(const uint32_t& size);
    void textScale(const sf::Vector2f& scale);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<std::shared_ptr<Button>> m_buttons;

    size_t m_active;
};

#endif // SWITCHER_H
