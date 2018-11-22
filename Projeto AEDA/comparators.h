#ifndef COMPARATORS_H
#define COMPARATORS_H

#define POINTER_OP(T,OP) Pointer_Operator<T,OP<T>>

template <class T>
class Sort_ID {
public:
	bool operator()(const T & lhs, const T  & rhs) const{
		return lhs.get_id() < rhs.get_id();
	}
};

template<class T>
class Sort_Time {
public:
	bool operator()(const T & lhs, const T & rhs) const{
		if (lhs.get_time() == rhs.get_time()) {
			Sort_ID<T> comp;
			return comp(lhs, rhs);
		}
		else
			return  lhs.get_time() < rhs.get_time();
	}
};

template<class T>
class Equal_ID {
public:
	bool operator()(const T & lhs, const T & rhs) {
		return lhs.get_id() == rhs.get_id();
	}
};

template<class T> class Equal_Time {
public:
	bool operator()(const T & lhs, const T & rhs) const{
		return lhs.get_id() == rhs.get_id();
	}
};

template<class T, class OP>
class Pointer_Operator {
private:
	const OP operation = OP();
public:
	bool operator()(const T* lhs, const T *rhs) const{
		return operation(*lhs, *rhs);
	}
};

template<class T>
class Pointer_Sort_ID {
public:
	bool operator()(const T *lhs, const T *rhs) const{
		return lhs->get_id() < rhs->get_id();
	}
};

template<class T>
class Pointer_Sort_Time {
public:
	bool operator()(const T *lhs, const T *rhs) const{
		if (lhs->get_time() == rhs->get_time()) {
			Pointer_Sort_ID<T> comp;
			return comp(lhs, rhs);
		}
		else
			return  lhs->get_time() < rhs->get_time();
	}
};

#endif //COMPARATORS_H
