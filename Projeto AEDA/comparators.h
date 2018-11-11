#ifndef COMPARATORS_H
#define COMPARATORS_H

template <class T> class Compare_ID {
    bool operator()(const T & lhs, const T  & rhs);
};

template<class T> class Compare_Date {
    bool operator()(const T & lhs, const T & rhs);
};

template <class T> bool Compare_ID::operator()(const T &lhs, const T &rhs) {
    return lhs.get_id() < rhs.get_id();
}

template <class T> bool Compare_Date::operator()(const T &lhs, const T &rhs) {
    if (lhs.get_date() == rhs.get_date()) {
        Compare_ID<T> comp;
        return comp(lhs,rhs);
    }
    else
        return  lhs.get_date() < rhs.get_date();
}

#endif //COMPARATORS_H
