#include <assert.h>
#include <tests.h>
#include <abstract.h>

void test_queue(structures::Queue<int>* queue) {
	for (int i = 0; i < SIZE; i++) {
		queue->enqueue(i);
	}

	assert(queue->size() == SIZE);
	assert(queue->front() == 0);
	assert(queue->back() == SIZE - 1);

	queue->clear();

	assert(queue->size() == 0);

	for (int i = 0; i < SIZE; i++) {
		queue->enqueue(i);
	}

	for (int i = 0; i < SIZE; i++) {
		assert(queue->dequeue() == i);
	}
}
