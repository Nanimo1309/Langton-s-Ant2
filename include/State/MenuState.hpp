#ifndef STATE_MENUSTATE_H
#define STATE_MENUSTATE_H

#include "MapControlState.hpp"

namespace State
{
    class MenuState:
        public State
    {
    public:
        MenuState(Application& application);
        virtual ~MenuState() = default;

        virtual void update(double timespan) override;

        virtual void input(const sf::Event& event) override;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        virtual void updateView(const sf::Vector2u& window) override;

        virtual void wakeUp() override;

    private:
        void resetActive();

        void definedSetting(size_t index);

        const Rules compileRules();

        static constexpr size_t m_switcherNumber = 12u;
        Switcher m_switcher[m_switcherNumber];
        static const sf::Vector2f m_switcherSize;

        Button m_reset;
        Button m_next;

        Switcher m_definedSetting;
        static const sf::Vector2f m_definedSettingSize;
    };
} // namespace State

#endif // STATE_MENUSTATE_H
