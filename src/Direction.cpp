#include "Direction.hpp"
#include <cmath>

const Direction Direction::Up(0.f);
const Direction Direction::Down(180.f);
const Direction Direction::Right(90.f);
const Direction Direction::Left(270.f);

Direction::Direction():
    m_direction     (0.f)
{}

Direction::Direction(const float& direction):
    m_direction     (direction)
{
    cutAngle();
}

Direction& Direction::operator+=(const float& direction)
{
    m_direction += direction;
    cutAngle();
    return *this;
}

Direction Direction::operator+(const float& direction) const
{
    return {m_direction + direction};
}

Direction& Direction::operator-=(const float& direction)
{
    m_direction -= direction;
    cutAngle();
    return *this;
}

Direction Direction::operator-(const float& direction) const
{
    return {m_direction - direction};
}

Direction::operator float()
{
    return m_direction;
}

Direction::operator float() const
{
    return m_direction;
}

float Direction::angle()
{
    return *this;
}

void Direction::cutAngle()
{
    m_direction = std::fmod(m_direction, 360.f);

    if(m_direction < 0.f)
        m_direction += 360.f;
}

