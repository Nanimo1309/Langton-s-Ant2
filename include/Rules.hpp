#ifndef RULES_H
#define RULES_H

#include "Headers.hpp"
#include "Direction.hpp"

class Rules
{
    struct Rule
    {
        sf::Color color;
        Direction direction;
    };

public:
    Rules();
    virtual ~Rules() = default;

    uint8_t getNext(uint8_t id) const;
    sf::Color getColor(uint8_t id) const;
    Direction getDirection(uint8_t id) const;

    void defaultId(uint8_t id);
    uint8_t defaultId() const;

    void addRule(const sf::Color& color, const Direction& direction);
    void reset();

    size_t number() const;

private:
    std::vector<Rule> m_rules;

    uint8_t m_defaultId;
};

#endif // RULES_H
