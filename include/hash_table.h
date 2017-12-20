#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <functional>

#include <array_list.h>
#include <linked_list.h>

namespace structures {

/**
 * @brief HashTable implementation
 *
 * @details This is a fast lookup data structure. It is a set, that is, it may
 * not have repeated entries. You can insert, remove, and search elements in
 * amortized constant time on average cases, and linear time in worst cases,
 * but that is unlikely to happen with a good hash function.
 *
 * This structure grows and shrinks as you insert and remove.
 *
 * @tparam T Data type of the elements
 * @tparam Hash Class that implements the hash function
 */
template <typename T, typename Hash = std::hash<T>>
class HashTable {
public:
	HashTable() = default;

	HashTable(const HashTable<T>& other) : HashTable(other.buckets_size) {
		auto list = other.items();
		for (std::size_t i = 0; i < list.size(); i++) {
			insert(list[i]);
		}
	}

	HashTable(HashTable<T>&& other)
		: buckets{std::move(other.buckets)}
		, buckets_size{std::move(other.buckets_size)}
		, _size{std::move(other._size)} {}

	HashTable<T>& operator=(const HashTable<T>& other) {
		HashTable<T> copy{other};
		std::swap(buckets_size, copy.buckets_size);
		std::swap(buckets, copy.buckets);
		std::swap(_size, copy._size);
		return *this;
	}

	HashTable<T>& operator=(HashTable<T>&& other) {
		HashTable<T> copy{std::move(other)};
		std::swap(buckets_size, copy.buckets_size);
		std::swap(buckets, copy.buckets);
		std::swap(_size, copy._size);
		return *this;
	}

	~HashTable() = default;

	/**
	 * @brief Inserts `data` into the table
	 *
	 * @details Puts `data` into its respective bucket, and if needed grows
	 * the table.
	 *
	 * @return false if `data` was already in the table, otherwise true
	 */
	bool insert(const T& data) {
		auto& bucket = buckets[hash(data)];
		if (bucket.contains(data)) {
			return false;
		} else {
			bucket.push_front(data);
			_size++;

			if (_size == buckets_size) {
				resize_table(buckets_size * 2);
			}

			return true;
		}
	}

	/**
	 * @brief Removes `data` from the table
	 *
	 * @details If found, removes `data` from the table, and shrinks the table
	 * if necessary.
	 *
	 * @return If `data` is not found, returns false, otherwise returns true.
	 */
	bool remove(const T& data) {
		try {
			auto& bucket = buckets[hash(data)];
			auto i = bucket.find(data);
			bucket.erase(i);
			_size--;

			if (_size <= buckets_size / 4 && buckets_size > starting_size) {
				std::size_t new_size = buckets_size / 2;
				if (new_size >= starting_size)
					resize_table(new_size);
			}

			return true;
		} catch (const std::out_of_range& e) {
			return false;
		}
	}

	/**
	 * @brief Returns true if the element is in the table
	 */
	bool contains(const T& data) const {
		return buckets[hash(data)].contains(data);
	}

	void clear() {
		HashTable<T> ht;
		*this = std::move(ht);
	}

	std::size_t size() const { return _size; }

	/**
	 * @brief Returns a list of the items that are on the table
	 */
	ArrayList<T> items() const {
		ArrayList<T> al{_size};

		for (std::size_t i = 0; i < buckets_size; i++) {
			for (std::size_t j = 0; j < buckets[i].size(); j++) {
				al.push_back(buckets[i].at(j));
			}
		}

		return std::move(al);
	}

private:
	explicit HashTable(std::size_t buckets_size_)
		: buckets{new LinkedList<T>[buckets_size_]}
		, buckets_size{buckets_size_} {}

	std::size_t hash(const T& data) const { return hashf(data) % buckets_size; }

	void resize_table(std::size_t new_size) {
		HashTable new_ht{new_size};

		auto list = items();
		for (std::size_t i = 0; i < list.size(); i++) {
			new_ht.insert(list.at(i));
		}

		*this = std::move(new_ht);
	}

	const static std::size_t starting_size{8};

	std::unique_ptr<LinkedList<T>[]> buckets {
		new LinkedList<T>[starting_size]
	};
	std::size_t buckets_size{starting_size};
	std::size_t _size{0};

	Hash hashf{};
};
}  // namespace structures

#endif
