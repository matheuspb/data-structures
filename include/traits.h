#ifndef TRAITS_H
#define TRAITS_H

#include <type_traits>

namespace traits {

template <template <typename> class>
struct is_list {
	const static bool value;
};

template <template <typename> class>
struct is_set {
	const static bool value;
};

template <template <typename> class>
struct type {
	const static std::string name;
};

template <template <typename> class T>
const bool is_list<T>::value = false;
template <template <typename> class T>
const bool is_set<T>::value = false;
template <template <typename> class T>
const std::string type<T>::name = "unknown";

}  // namespace traits

#endif
