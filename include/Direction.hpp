#ifndef DIRECTION_H
#define DIRECTION_H

class Direction
{
public:
    Direction();
    Direction(const float& direction);
    virtual ~Direction() = default;

    Direction& operator+=(const float& direction);
    Direction operator+(const float& direction) const;

    Direction& operator-=(const float& direction);
    Direction operator-(const float& direction) const;

    operator float();
    operator float() const;

    float angle();

    static const Direction Up;
    static const Direction Down;
    static const Direction Right;
    static const Direction Left;

private:
    void cutAngle();

    float m_direction;
};

#endif // DIRECTION_H
