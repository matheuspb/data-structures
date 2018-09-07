#ifndef STRUCTURES_UTILS_H
#define STRUCTURES_UTILS_H

#include <memory>

namespace structures {

#if __cplusplus < 201402L
template <typename T, typename... Args>
typename std::enable_if<not std::is_array<T>::value, std::unique_ptr<T>>::
	type constexpr make_unique(Args&&... args) {
	return std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
}

template <typename T, typename... Args>
typename std::enable_if<std::is_array<T>::value, std::unique_ptr<T>>::
	type constexpr make_unique(std::size_t size) {
	using type = typename std::remove_extent<T>::type;
	return std::unique_ptr<T>{new type[size]};
}
#else
using std::make_unique;
#endif
}  // namespace structures

#endif
