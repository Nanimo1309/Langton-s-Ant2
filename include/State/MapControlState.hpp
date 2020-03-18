#ifndef STATE_MAPCONTROLSTATE_H
#define STATE_MAPCONTROLSTATE_H

#include "MapState.hpp"

namespace State
{
    class MapControlState:
        public MapState
    {
    public:
        MapControlState(Application& application, const Rules& rules);
        virtual ~MapControlState() = default;

        virtual void update(double timespan) override;

        virtual void input(const sf::Event& event) override;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        virtual void updateView(const sf::Vector2u& window) override;

        virtual void wakeUp() override;

    protected:
        virtual void moveTime(double time) override;

    private:
        void setupCamera();
        void zoom(int zoom);

        void updateSpeed();

        Camera m_camera;
        float m_yToX;
        float m_xPixelsZoom;

        Button m_run;
        Button m_reset;
        Button m_back;

        sf::Text m_steps;

        Switcher m_speedSwitcher;
        std::vector<std::shared_ptr<Button>> m_switcherButtons;
    };
} // namespace State

#endif // STATE_MAPCONTROLSTATE_H
