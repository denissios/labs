#ifndef __MY_VECTOR_HPP_INCLUDED__
#define __MY_VECTOR_HPP_INCLUDED__

#include <algorithm>
#include <cassert>
#include <iterator>

/*!
    \brief array class for storing data
    MyVector is stored as an dynamic array
    */
template<typename _T>
class MyVector
{
public:
    /*class iterator;
    class reverse_iterator;*/

    using iterator = _T*;
    using const_iterator = const _T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    inline MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    inline MyVector(int length)
    {
        if (length < 0 || length > m_size - 1)
            throw std::exception("invalid length");
        m_size = length;
        m_capacity = 2 * length;
        m_data = new _T[m_capacity];
    }

    inline MyVector(const std::initializer_list<_T>& list)
    {
        int size = list.size();

        m_size = size;
        m_capacity = size;


        m_data = new _T[m_capacity];

        size_t i = 0;
        for (auto & element : list) {
            m_data[i] = element;
            i++;
        }
    }

    inline MyVector(MyVector&& other) noexcept : 
        m_data(std::move(other.m_data)),
        m_size(std::move(other.m_size)),
        m_capacity(std::move(other.m_capacity))
    {
        other.m_data = nullptr;
        other.m_size = other.m_capacity = 0;
    }

    inline MyVector& operator=(MyVector&& other) noexcept
    {
        if (this != &other) {
            std::for_each(begin(), end(), [](auto& el) { el.~_T(); });
            delete[] reinterpret_cast<char*>(m_data);

            m_data = std::move(other.m_data);
            m_size = std::move(other.m_size);
            m_capacity = std::move(other.m_capacity);

            other.m_data = nullptr;
            other.m_size = other.m_capacity = 0;
        }
        return *this;
    }

    inline ~MyVector()
    {
        std::for_each(begin(), end(), [](auto& el) { el.~_T(); });
        //delete[] m_data;
        delete[] reinterpret_cast<char*>(m_data);
        m_size = 0;
        m_capacity = 0;
    }

    /*!
    \brief return size
    */
    [[nodiscard]] inline constexpr size_t size() const noexcept { return m_size; }

    /*!
    \brief return capacity
    */
    [[nodiscard]] inline constexpr size_t capacity() const noexcept { return m_capacity; }

    inline constexpr bool operator==(const MyVector& v) const { return m_size == v.m_size && std::equal(m_data, m_data + m_size, v.m_data); }

    inline constexpr bool operator<(const MyVector& v) const { return std::lexicographical_compare(m_data, m_data + m_size, v.m_data, v.m_data + v.m_size); }

    [[nodiscard]] inline constexpr _T& operator[](const int index) const { return m_data[index]; }

    /*!
    \brief accessing an array element
    \return reference to array element
    \throw std :: out_of_range when trying to access a nonexistent array element
    */
    [[nodiscard]]
    inline _T& at(int index)
    {
        if (index < 0 || index > m_size - 1)
            throw std::exception("out of range exception");
        else
            return m_data[index];
    }

    /*!
    \brief accessing an array element
    \return reference to array element
    \throw std :: out_of_range when trying to access a nonexistent array element
    */
    [[nodiscard]]
    inline const _T& at(int index) const
    {
        if (index < 0 || index > m_size - 1)
            throw std::exception("out of range exception");
        else
            return m_data[index];
    }

    /*!
    \brief accessing an array element
    \return a reference to the first element in the vector.
    */
    [[nodiscard]] inline const _T& front() const { return m_data[0]; }

    /*!
    \brief accessing an array element
    \return a reference to the first element in the vector.
    */
    [[nodiscard]] inline _T& front() { return m_data[0]; }

    /*!
    \brief accessing an array element
    \return a reference to the last element in the vector.
    */
    [[nodiscard]] inline const _T& back() const { return m_data[m_size - 1]; }

    /*!
    \brief accessing an array element
    \return a reference to the last element in the vector.
    */
    [[nodiscard]] inline _T& back() { return m_data[m_size - 1]; }

    /*!
    \brief push an element to the back of array
    \return void
    */
    void push_back(_T number)
    {
        if (m_size == m_capacity) {
            ++m_capacity *= 2;
            static_assert(sizeof(char) == 1);
            _T* temp = reinterpret_cast<_T*>(new char[m_capacity * sizeof(_T)]);

            for (size_t i = 0; i < m_size; ++i)
                new(temp + i) _T(std::move(m_data[i]));

            //delete[] m_data;
            delete[] reinterpret_cast<char*>(m_data);
            m_data = temp;
        }

        new(m_data + m_size) _T(number);
        //m_data[m_size] = number;
        m_size++;
    }

    /*!
    \brief pop the last element of the array
    \return void
    */
    void pop_back()
    {
        if (!m_size)
            return;

        m_data[m_size].~_T();
        m_size--;
    }

    /*!
    \brief pop the last element of the array
    \return a reference to the newly emplaced element
    */
    template<typename... ARGS>
    typename _T& emplace_back(ARGS&&... args)
    {
        if (m_size == m_capacity) {
            ++m_capacity *= 2;
            static_assert(sizeof(char) == 1);
            _T* temp = reinterpret_cast<_T*>(new char[m_capacity * sizeof(_T)]);

            for (size_t i = 0; i < m_size; ++i)
                new(temp + i) _T(std::move(m_data[i]));

            //delete[] m_data;
            delete[] reinterpret_cast<char*>(m_data);
            m_data = temp;
        }

        new(m_data + m_size) _T(std::forward<ARGS>(args)...);
        //m_data[m_size] = _T(std::forward<ARGS>(args)...);
        ++m_size;
        return back();
    }

    /*!
    \brief pop the last element of the array
    \return an iterator that points to the newly emplaced element
    */
    template<typename... ARGS>
    inline typename _T* emplace(const _T* pos, ARGS&&... args)
    {
        size_t dist = pos - begin();

        if (dist == m_capacity)
        {
            emplace_back(_T(std::forward<_T>(args)...));
        }
        else
        {
            if (m_size == m_capacity)
            {
                ++m_capacity *= 2;
                _T* temp = new _T[m_capacity];

                for (size_t i = 0; i < m_size; ++i)
                    temp[i] = m_data[i];

                delete[] m_data;
                m_data = temp;
            }

            std::move_backward(begin() + dist, end(), end() + 1);

            _T* iter = &m_data[dist];

            *iter = std::move(_T(std::forward<ARGS>(args)...));

            ++m_size;

            return iter;
        }
    }

    /*!
    \brief erase the element of the array
    \return an iterator that points to the erased element
    */
    inline typename _T* erase(const_iterator pos)
    {
        const size_t dist = pos - begin();

        if (m_size != 0)
            --m_size;


        if (m_size == 0)
            m_capacity = 0;
        else
            ++m_capacity *= 2;

        if (m_capacity != 0)
        {
            //_T* temp = new _T[m_capacity];
            pos->~_T();
            //_T* temp = reinterpret_cast<_T*>(alignas(_T) new char[m_capacity * sizeof(_T)]);

            std::move(pos + 1, end(), pos);
        }

        return &m_data[dist];
    }

    /*!
    \brief pop the last element of the array
    \return an iterator that points to the newly emplaced element
    */
    inline typename _T* erase(iterator first, iterator last)
    {
        const size_t dist = first - begin();

        std::for_each(first, last, [](auto& el) { el.~_T(); });

        const size_t n = last - first;

        std::move(last, end(), first);

        m_size -= n;

        return &m_data[dist];
    }

    /*!
    \brief clear the array
    \return void
    */
    inline void clear() noexcept
    {
        std::for_each(begin(), end(), [](auto& el) { el.~_T(); });
        m_size = 0;
    }

    /*!
    \brief accessing an array element
    \return an iterator to the first element of the array
    */
    inline typename iterator begin() noexcept { return m_data; }

    /*!
    \brief accessing an array element
    \return an iterator to the first element of the array
    */
    inline typename const_iterator cbegin() const noexcept { return m_data; }

    /*!
   \brief accessing an array element
   \return an iterator to the first element of the array
   */
    inline typename iterator end() noexcept { return m_data + m_size; }

    /*!
   \brief accessing an array element
   \return an iterator to the first element of the array
   */
    inline typename const_iterator cend() const noexcept { return m_data + m_size; }

    /*!
   \brief accessing an array element
   \return an iterator to the last element of the array
   */
    inline typename reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

    /*!
   \brief accessing an array element
   \return an iterator to the last element of the array
   */
    inline typename reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    class Iterator
    {
    public:
        Iterator(_T* it) : m_it(it) {}
        
        inline constexpr _T& operator+(int n) noexcept { return *(m_it + n); }
        inline constexpr _T& operator-(int n) noexcept { return *(m_it - n); }

        inline constexpr _T& operator++(int) noexcept { return *m_it++; }
        inline constexpr _T& operator--(int) noexcept { return *m_it--; }
        inline constexpr _T& operator++() noexcept { return *++m_it; }
        inline constexpr _T& operator--() noexcept { return *--m_it; }

        inline constexpr bool operator!=(const iterator& it) noexcept { return m_it != it.m_it; }
        inline constexpr bool operator==(const iterator& it) noexcept { return m_it == it.m_it; }
        inline constexpr _T& operator*() noexcept { return *m_it; }

    private:
        _T* m_it;
    };

    class Reverse_Iterator
    {
    public:
        Reverse_Iterator(_T* it) : m_it(it) {}

        inline constexpr _T& operator+(int n) noexcept { return *(m_it - n); }

        inline constexpr _T& operator++(int) noexcept { return *m_it--; }
        inline constexpr _T& operator++() noexcept { return *--m_it; }

        inline constexpr bool operator!=(const reverse_iterator& it) noexcept { return m_it != it.m_it; }
        inline constexpr bool operator==(const reverse_iterator& it) noexcept { return m_it == it.m_it; }
        inline constexpr _T& operator*() noexcept { return *m_it; }

    private:
        _T* m_it;
    };

private:
    _T* m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif /* !__MY_VECTOR_HPP_INCLUDED__ */