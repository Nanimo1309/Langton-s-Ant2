#ifndef STATE_MAPSTATE_H
#define STATE_MAPSTATE_H

#include "CloseState.hpp"

namespace State
{
    class MapState:
        public State
    {
    public:
        MapState(Application& application, const Rules& rules);
        virtual ~MapState() = default;

        virtual void update(double timespan) override;

        virtual void input(const sf::Event& event) override;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        virtual void updateView(const sf::Vector2u& window) override;

        virtual void wakeUp() override;

    protected:
        void run(bool run);
        bool run();

        virtual void moveTime(double time);

        void initMap();

        sf::Vector2u mapSize() const;
        sf::Vector2u mapCenter() const;
        sf::Vector2i antPosition() const;

        size_t steps();

    private:
        Map m_map;
        Ant m_ant;

        size_t m_steps;

        bool m_run;

        double m_toNextMove;
        double m_moveTime;
    };
} // namespace State

#endif // STATE_MAPSTATE_H
