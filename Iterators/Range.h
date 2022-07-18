

#ifndef LAB6_RANGE_H
#define LAB6_RANGE_H

template<typename Range>
class RangeIterator {
private:

public:
    using ValueType = typename Range::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
public:
    explicit RangeIterator(ValueType ptr, ValueType step) : m_Ptr(ptr), step(step) {};

    RangeIterator& operator++() {
        m_Ptr += step;
        return *this;
    }

    RangeIterator operator++(int) {
        auto iterator = *this;
        ++(*this);
        return iterator;
    }

    RangeIterator& operator--() {
        m_Ptr -= step;
        return *this;
    }

    ReferenceType operator*() {
        return m_Ptr;
    }

    PointerType operator->() {
        return &m_Ptr;
    }

    bool operator==(const RangeIterator& other) const {
        return m_Ptr == other.m_Ptr;
    }

    bool operator!=(const RangeIterator& other) const {
        return m_Ptr != other.m_Ptr;
    }

private:
    ValueType m_Ptr;
    ValueType step;

};


template <typename T>
class Range{
private:
    T start;
    T stop;
    T step;
public:
    using ValueType = T;
    using Iterator = RangeIterator<Range<T>>;
public:
    ValueType lastRealStop() {
        ValueType realStop = start;
        while(realStop < stop) {
            realStop += step;
        }
        return realStop;
    }

    Range(T start, T stop, T step) :start(start), stop(stop), step(step){}
    Range(T start, T stop) :start(start), stop(stop), step(1){}
    explicit Range(T stop) :start(0), stop(stop), step(1){}

    Iterator begin() {
        return Iterator(start, step);
    }

    Iterator end() {
        return Iterator(lastRealStop(), step);
    }

};

template<typename T>
Range<T> make_range(T start, T stop, T step) {
    return Range(start, stop, step);
}

template<typename T>
Range<T> make_range(T stop) {
    return Range(stop);
}


#endif //LAB6_RANGE_H
