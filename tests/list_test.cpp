#include <initializer_list>
#include <assert.h>

#include <tests.h>
#include <abstract.h>

void test_list(structures::List<int>* list) {
	for (int i = 0; i < SIZE - 1; i++) {
		list->push_front(i);
		assert(list->contains(i));
		assert(list->find(i) == 0);
	}

	list->insert(SIZE, SIZE/2);
	assert(list->at(SIZE/2) == SIZE);
	assert(list->size() == SIZE);
	assert(list->erase(SIZE/2) == SIZE);

	for (int i = 0; i < SIZE - 1; i++) {
		assert(list->pop_back() == i);
		assert(!list->contains(i));
		assert(list->find(i) == list->size());
	}

	assert(list->size() == 0);

	for (int i = 0; i < SIZE; i++) {
		list->push_back(i);
		assert(list->contains(i));
		assert(list->find(i) == (unsigned) i);
	}

	assert(list->size() == SIZE);

	for (int i = 0; i < SIZE; i++) {
		assert(list->at(list->find(i)) == i);
	}

	for (int i = 0; i < SIZE; i++) {
		assert(list->pop_front() == i);
		assert(!list->contains(i));
		assert(list->find(i) == list->size());
	}

	assert(list->size() == 0);

	for (int i = 0; i < SIZE; i++) {
		list->push_back(i);
	}

	list->clear();
	assert(list->size() == 0);
}
