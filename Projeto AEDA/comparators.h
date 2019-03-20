/*
 * (c) 2018 Griné, Matos, and Simões
 * This software is provided under the MIT License.
 * To obtain a copy of this license, please read the file LICENSE at the root of the repository, or visit
 * https://opensource.org/licenses/MIT
 */

#ifndef COMPARATORS_H
#define COMPARATORS_H
/**
 * @defgroup comparators
 * Templates for operators that do comparison and sorting operations
 * @{
 */
/**
 * Implements an operator on pointers of an object
 * @param T Type of object
 * @param OP Operator template
 */
#define POINTER_OP(T,OP) Pointer_Operator<T,OP<T>>

/**
 * Operator template for sorting objects by ID
 * 
 * @tparam T Type of object that will be sorted
 */
template <class T>
class Sort_ID {
public:
	/**
	 * Implements a LESS_THAN type comparator for objects' IDs
	 * 
	 * @param lhs Object one, left side in infix notation
	 * @param rhs Object two, right side in infix notation
	 */
	bool operator()(const T & lhs, const T  & rhs) const{
		return lhs.get_id() < rhs.get_id();
	}
};

/**
 * Operator template for sorting objects by their time stamps, secondarily by their IDs
 * 
 * @tparam T Type of object to sort
 */
template<class T>
class Sort_Time {
public:
	/**
	 * Implements a LESS_THAN type comparator for objects' time objects, with ID as backup
	 * 
	 * @param lhs Object one, left side in infix notation
	 * @param rhs Object two, right side in infix notation
	 */
	bool operator()(const T & lhs, const T & rhs) const{
		if (lhs.get_time() == rhs.get_time()) {
			Sort_ID<T> comp;
			return comp(lhs, rhs);
		}
		else
			return  lhs.get_time() < rhs.get_time();
	}
};

/**
 * Implements equivalence relationship for objects' IDs
 * 
 * @tparam T Type of object to compare
 */
template<class T>
class Equal_ID {
public:
	/**
	 * EQUAL_TO type operator for objects' IDs
	 * 
	 * @param lhs Infix left hand side object
	 * @param rhs Infix right hand side object
	 */
	bool operator()(const T & lhs, const T & rhs) {
		return lhs.get_id() == rhs.get_id();
	}
};

/**
 * Implements equivalence relationship for objects' time stamps
 * 
 * @tparam T Type of object to compare
 */
template<class T> class Equal_Time {
public:
	/**
	 * EQUAL_TO type operator for objects' time stamps
	 * 
	 * @param lhs Infix left hand side object
	 * @param rhs Infix right hand side object
	 */
	bool operator()(const T & lhs, const T & rhs) const{
		return lhs.get_id() == rhs.get_id();
	}
};

/**
 * Applies an operator to pointers of a certain type
 * 
 * @tparam T Type of object
 * @tparam OP Binary boolean operator
 */
template<class T, class OP>
class Pointer_Operator {
private:
	const OP operation = OP();
public:
	/**
	 * Applies an operator to the objects pointed
	 * 
	 * @param Pointer to the infix left hand side object
	 * @param Pointer to the infix right hand side object
	 */
	bool operator()(const T* lhs, const T *rhs) const{
		return operation(*lhs, *rhs);
	}
};

/**
 * Applies Sort_ID style operator to the pointed objects
 * 
 * @tparam T Object type
 */
template<class T>
class Pointer_Sort_ID {
public:
	/**
	 * Implements a LESS_THAN type comparator for objects' IDs
	 * 
	 * @param lhs Pointer to object one, left side in infix notation
	 * @param rhs Pointer to object two, right side in infix notation
	 */
	bool operator()(const T *lhs, const T *rhs) const{
		return lhs->get_id() < rhs->get_id();
	}
};

/**
 * Applies Sort_Time style operator to the pointed objects
 * 
 * @tparam T Object type
 */
template<class T>
class Pointer_Sort_Time {
public:
	/**
	 * Implements a LESS_THAN type comparator for objects' time objects, with ID as backup
	 * 
	 * @param lhs Pointer to object one, left side in infix notation
	 * @param rhs Pointer to bject two, right side in infix notation
	 */
	bool operator()(const T *lhs, const T *rhs) const{
		if (lhs->get_time() == rhs->get_time()) {
			Pointer_Sort_ID<T> comp;
			return comp(lhs, rhs);
		}
		else
			return  lhs->get_time() < rhs->get_time();
	}
};

/** @} */
#endif//COMPARATORS_H
