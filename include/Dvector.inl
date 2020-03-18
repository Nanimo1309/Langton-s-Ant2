template<class T>
T& Dvector<T>::operator[](size_t index)
{
    if(index < m_front.size())
        return m_front[m_front.size() - 1 - index];
    else
        return m_back[index - m_front.size()];
}

template<class T>
const T& Dvector<T>::operator[](size_t index) const
{
    if(index < m_front.size())
        return m_front[m_front.size() - 1 - index];
    else
        return m_back[index - m_front.size()];
}

template<class T>
T& Dvector<T>::at(size_t index)
{
    if(index < m_front.size())
        return m_front.at(m_front.size() - 1 - index);
    else
        return m_back.at(index - m_front.size());
}

template<class T>
void Dvector<T>::push_front(const T& value)
{
    m_front.push_back(value);
}

template<class T>
void Dvector<T>::push_front(T&& value)
{
    m_front.push_back(std::move(value));
}

template<class T>
void Dvector<T>::insert(size_t index, const T& value)
{
    if(index == 0)
        m_front.push_back(value);
    else if(index < m_front.size())
        m_front.insert(m_front.begin() + (m_front.size() - index), value);
    else
        m_back.insert(m_back.begin() + (index - m_front.size()), value);
}

template<class T>
void Dvector<T>::insert(size_t index, T&& value)
{
    if(index == 0)
        m_front.push_back(std::move(value));
    else if(index < m_front.size())
        m_front.insert(m_front.begin() + (m_front.size() - index), std::move(value));
    else
        m_back.insert(m_back.begin() + (index - m_front.size()), std::move(value));
}

template<class T>
void Dvector<T>::push_back(const T& value)
{
    m_back.push_back(value);
}

template<class T>
void Dvector<T>::push_back(T&& value)
{
    m_back.push_back(std::move(value));
}

template<class T>
template<class... Args>
void Dvector<T>::emplace_front(Args&&... args)
{
    m_front.emplace_back(args...);
}

template<class T>
template<class... Args>
void Dvector<T>::emplace(size_t index, Args&&... args)
{
    if(index == 0)
        m_front.push_back(std::move(args...));
    else if(index < m_front.size())
        m_front.emplace(m_front.begin() + (m_front.size() - index), args...);
    else
        m_back.emplace(m_back.begin() + (index - m_front.size()), args...);
}

template<class T>
template<class... Args>
void Dvector<T>::emplace_back(Args&&... args)
{
    m_back.emplace_back(args...);
}

template<class T>
bool Dvector<T>::empty() const
{
    return m_front.empty() && m_back.empty();
}

template<class T>
size_t Dvector<T>::size() const
{
    return m_front.size() + m_back.size();
}

template<class T>
void Dvector<T>::clear()
{
    m_front.clear();
    m_back.clear();
}

template<class T>
void Dvector<T>::pop_front()
{
    if(!m_front.empty())
        m_front.pop_back();
    else if(!m_back.empty())
        m_back.erase(m_back.begin());
}

template<class T>
void Dvector<T>::erase(size_t index)
{
    if(index < m_front.size())
        m_front.erase(m_front.begin() + (m_front.size() - 1 - index));
    else
        m_back.erase(m_back.begin() + (index - m_front.size()));
}

template<class T>
void Dvector<T>::pop_back()
{
    if(!m_back.empty())
        m_back.pop_back();
    else if(!m_front.empty())
        m_front.erase(m_front.begin());
}

template<class T>
size_t Dvector<T>::front_capacity() const
{
    return m_front.capacity();
}

template<class T>
size_t Dvector<T>::back_capacity() const
{
    return m_back.capacity();
}

template<class T>
void Dvector<T>::front_reserve(size_t size)
{
    m_front.reserve(size);
}

template<class T>
void Dvector<T>::back_reserve(size_t size)
{
    m_back.reserve(size);
}
