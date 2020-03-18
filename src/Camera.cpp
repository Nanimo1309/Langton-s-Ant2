#include "Camera.hpp"

Camera::Camera():
    m_viewport  {0.f, 0.f, 1.f, 1.f},
    m_size      {1.f, 1.f},
    m_speed     (0),
    m_curSize   {1.f, 1.f},
    m_destSize  {1.f, 1.f}
{}

void Camera::update(double timespan)
{
    if(!m_speed)
    {
        m_curCenter = m_destCenter;
        m_curSize = m_destSize;

        return;
    }

    if(m_curCenter.x < m_destCenter.x)
    {
        m_curCenter.x += m_speed * timespan * 0.5f;

        if(m_curCenter.x > m_destCenter.x)
            m_curCenter.x = m_destCenter.x;
    }
    else if(m_curCenter.x > m_destCenter.x)
    {
        m_curCenter.x -= m_speed * timespan * 0.5f;

        if(m_curCenter.x < m_destCenter.x)
            m_curCenter.x = m_destCenter.x;
    }

    if(m_curCenter.y < m_destCenter.y)
    {
        m_curCenter.y += m_speed * timespan * 0.5f;

        if(m_curCenter.y > m_destCenter.y)
            m_curCenter.y = m_destCenter.y;
    }
    else if(m_curCenter.y > m_destCenter.y)
    {
        m_curCenter.y -= m_speed * timespan * 0.5f;

        if(m_curCenter.y < m_destCenter.y)
            m_curCenter.y = m_destCenter.y;
    }

    if(m_curSize.x < m_destSize.x)
    {
        m_curSize.x += m_speed * timespan;

        if(m_curSize.x > m_destSize.x)
            m_curSize.x = m_destSize.x;
    }
    else if(m_curSize.x > m_destSize.x)
    {
        m_curSize.x -= m_speed * timespan;

        if(m_curSize.x < m_destSize.x)
            m_curSize.x = m_destSize.x;
    }

    if(m_curSize.y < m_destSize.y)
    {
        m_curSize.y += m_speed * timespan;

        if(m_curSize.y > m_destSize.y)
            m_curSize.y = m_destSize.y;
    }
    else if(m_curSize.y > m_destSize.y)
    {
        m_curSize.y -= m_speed * timespan;

        if(m_curSize.y < m_destSize.y)
            m_curSize.y = m_destSize.y;
    }
}

void Camera::sync()
{
    m_curCenter = m_destCenter;
    m_curSize = m_destSize;
}

void Camera::viewport(const sf::FloatRect& viewport)
{
    m_viewport = viewport;
}

sf::FloatRect Camera::viewport()
{
    return m_viewport;
}

void Camera::center(const sf::Vector2f& center, bool smooth)
{
    if(m_size.x <= m_destSize.x)
    {
        m_destCenter.x = center.x;

        if(!smooth)
            m_curCenter.x = m_destCenter.x;
    }

    if(m_size.y <= m_destSize.y)
    {
        m_destCenter.y = center.y;

        if(!smooth)
            m_curCenter.y = m_destCenter.y;
    }

    m_center = center;
}

sf::Vector2f Camera::center()
{
    return m_center;
}

void Camera::size(const sf::Vector2f& size, bool smooth)
{
    if(size.x > m_size.x)
    {
        if(m_size.x <= m_destSize.x)
        {
            m_destSize.x = std::max(size.x, m_destSize.x);

            if(!smooth)
                m_curSize.x = m_destSize.x;
        }
    }
    else
    {
        if(m_size.x >= m_destSize.x)
        {
            m_destSize.x = std::min(size.x, m_destSize.x);

            if(!smooth)
                m_curSize.x = m_destSize.x;
        }
    }

    if(size.y > m_size.y)
    {
        if(m_size.y <= m_destSize.y)
        {
            m_destSize.y = std::max(size.y, m_destSize.y);

            if(!smooth)
                m_curSize.y = m_destSize.y;
        }
    }
    else
    {
        if(m_size.y >= m_destSize.y)
        {
            m_destSize.y = std::min(size.y, m_destSize.y);

            if(!smooth)
                m_curSize.y = m_destSize.y;
        }
    }

    m_size = size;
}

sf::Vector2f Camera::size()
{
    return m_size;
}

void Camera::speed(float speed)
{
    m_speed = speed;
}

void Camera::viewCenter(const sf::Vector2f& viewCenter, bool smooth)
{
    m_destCenter = viewCenter;

    checkCenter();

    if(!smooth)
        m_curCenter = m_destCenter;
}

sf::Vector2f Camera::viewCenter()
{
    return m_destCenter;
}

void Camera::viewSize(const sf::Vector2f& viewSize, bool smooth)
{
    m_destSize = viewSize;

    checkCenter();

    if(!smooth)
    {
        m_curSize = m_destSize;
        m_curCenter = m_destCenter;
    }
}

sf::Vector2f Camera::viewSize()
{
    return m_destSize;
}

sf::View Camera::view() const
{
    sf::View temp(m_curCenter, m_curSize);
    temp.setViewport(m_viewport);

    return temp;
}

void Camera::checkCenter()
{
    if(m_size.x <= m_destSize.x)
        m_destCenter.x = m_center.x;
    else
    {
        float delta = (m_size.x - m_destSize.x) * 0.5f;

        if(m_destCenter.x < m_center.x - delta)
            m_destCenter.x = m_center.x - delta;
        else if(m_destCenter.x > m_center.x + delta)
            m_destCenter.x = m_center.x + delta;
    }

    if(m_size.y <= m_destSize.y)
        m_destCenter.y = m_center.y;
    else
    {
        float delta = (m_size.y - m_destSize.y) * 0.5f;

        if(m_destCenter.y < m_center.y - delta)
            m_destCenter.y = m_center.y - delta;
        else if(m_destCenter.y > m_center.y + delta)
            m_destCenter.y = m_center.y + delta;
    }
}
