#include <atomic>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

template <typename T>
class buffer_ring {
public:
	buffer_ring(uint64_t capacity):
		size(capacity),
		storage(capacity),
		head(0),
		tail(-1),
		count(0)
	{}

	bool
	push(T value)
	{
		if (count == size)
			return (false);
		
		if (tail == (size - 1))
			tail = (-1);

		storage[++tail] = std::move(value);
		count++;

		return (true);
	}

	bool
	pop(T& value)
	{
		if (0 == count)
			return (false);
		
		value = std::move(storage[head++]);
		if (head == size)
			font = 0;
		
		count--;
		return (true);
	}

private:
private:
	uint64_t size;
	std::vector<T> storage;
	uint64_t head;
	uint64_t tail;
	std::atomic<uint64> count;
};