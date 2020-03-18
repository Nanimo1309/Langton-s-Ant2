#ifndef DVECTOR_H
#define DVECTOR_H

#include <vector>
#include <cstddef>

template<class T>
class Dvector
{
    public:
        Dvector() = default;
        virtual ~Dvector() = default;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        T& at(size_t index);

        void push_front(const T& value);
        void push_front(T&& value);

        void insert(size_t index, const T& value);
        void insert(size_t index, T&& value);

        void push_back(const T& value);
        void push_back(T&& value);

        template<class... Args>
        void emplace_front(Args&&... args);

        template<class... Args>
        void emplace(size_t index, Args&&... args);

        template<class... Args>
        void emplace_back(Args&&... args);

        bool empty() const;
        size_t size() const;

        void clear();
        void pop_front();
        void erase(size_t index);
        void pop_back();

        size_t front_capacity() const;
        size_t back_capacity() const;

        void front_reserve(size_t size);
        void back_reserve(size_t size);

    private:
        std::vector<T> m_front;
        std::vector<T> m_back;
};

#include "Dvector.inl"

#endif // DVECTOR_H
