#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Headers.hpp"

class Camera
{
public:
    Camera();
    virtual ~Camera() = default;

    void update(double timespan);
    void sync();

    void viewport(const sf::FloatRect& viewport);
    sf::FloatRect viewport();

    void center(const sf::Vector2f& center, bool smooth = false);
    sf::Vector2f center();

    void size(const sf::Vector2f& size, bool smooth = false);
    sf::Vector2f size();

    void speed(float speed);

    void viewCenter(const sf::Vector2f& viewCenter, bool smooth = false);
    sf::Vector2f viewCenter();

    void viewSize(const sf::Vector2f& viewSize, bool smooth = false);
    sf::Vector2f viewSize();

    sf::View view() const;

private:
    void checkCenter();

    sf::FloatRect m_viewport;
    sf::Vector2f m_center;
    sf::Vector2f m_size;

    float m_speed;

    sf::Vector2f m_curCenter;
    sf::Vector2f m_curSize;

    sf::Vector2f m_destCenter;
    sf::Vector2f m_destSize;
};

#endif // CAMERA_HPP
