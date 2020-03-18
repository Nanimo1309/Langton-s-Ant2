#ifndef STATE_CLOSESTATE_H
#define STATE_CLOSESTATE_H

#include "Application.hpp"

namespace State
{
    class CloseState:
        public State
    {
    public:
        CloseState(Application& application, State* prev);
        virtual ~CloseState() = default;

        virtual void update(double timespan) override;

        virtual void input(const sf::Event& event) override;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        virtual void updateView(const sf::Vector2u& window) override;

        virtual void wakeUp() override;

    private:
        State* m_prev;

        sf::RectangleShape m_shadow;
        constexpr static float m_shadowLevel = 0.7, m_shadowSpeed = 0.7;
        float m_curShadow;

        sf::Texture m_tWindow;
        sf::Sprite m_sWindow;

        sf::Text m_text;

        Button m_ok;
        Button m_cancel;

        uint8_t m_blink;
        double m_blinkTime;
    };
} // namespace State

#endif // STATE_CLOSESTATE_H
