#ifndef BUTTON_H
#define BUTTON_H

#include "Headers.hpp"

class Button:
    public sf::Drawable
{
    friend class Switcher;

public:
    Button();
    virtual ~Button() = default;

    bool check(const sf::Event& event);
    bool check();

    void texture(std::shared_ptr<sf::Texture> texture);
    std::shared_ptr<sf::Texture> texture() const;

    void position(const sf::Vector2f& pos);
    sf::Vector2f position() const;

    void size(const sf::Vector2f& siz);
    sf::Vector2f size() const;

    void color(const sf::Color& color);
    sf::Color color() const;

    void hoverColor(const sf::Color& color);
    sf::Color hoverColor() const;

    void activeColor(const sf::Color& color);
    sf::Color activeColor() const;

    void textColor(const sf::Color& color);
    sf::Color textColor() const;

    void textOutlineColor(const sf::Color& color);
    sf::Color textOutlineColor() const;
    void textOutlineThickness(const float& size);

    void textFont(const sf::Font& font);
    void textAdd(const sf::String& text);
    void textNext();
    void textClear();
    void textSize(const uint32_t& size);
    void textScale(const sf::Vector2f& scale);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    enum State
    {
        stateDefault,
        stateHover,
        stateActive
    };

    void updateTextPosition();

    void updateColor();

    std::shared_ptr<sf::Texture> m_texture;
    sf::Sprite m_sprite;

    State m_state;

    sf::Color m_color;
    sf::Color m_hoverColor;
    sf::Color m_activeColor;

    sf::Text m_text;
    std::queue<std::string> m_textQueue;
};

#endif // BUTTON_H
