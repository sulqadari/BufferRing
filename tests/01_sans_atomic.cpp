#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

template <typename T>
class ring_buffer
{
public:
	ring_buffer(size_t capacity):
		size(capacity),
		storage(capacity + 1),
		tail(0),
		head(0)
	{}

	bool push(T value)
	{
		size_t curr_tail = tail;
		size_t curr_head = head;

		if (get_next(curr_tail) == curr_head) {
			return (false);
		}

		storage[curr_tail] = std::move(value);
		tail = get_next(curr_tail);

		std::cout << "push::tail: " << tail << std::endl;
		return (true);
	}

	bool pop(T& value)
	{
		size_t curr_tail = tail;
		size_t curr_head = head;

		if (curr_tail == curr_head) {
			return (false);
		}

		value = std::move(storage[curr_head]);
		head = get_next(curr_head);
		std::cout << "pop::head: " << head << std::endl;

		return (true);
	}

private:
	size_t get_next(size_t slot) const
	{
		return (slot + 1) % size;
	}

private:
	size_t size;
	std::vector<T> storage;
	size_t tail;
	size_t head;
};

static void
test(void)
{
	int count = 10000000;
	uint64_t sum = 0;
	ring_buffer<int> buffer(1024);
	auto start = std::chrono::steady_clock::now();

	std::thread producer([&]()
	{
		for (int i = 0; i < count; ++i)
		{
			while (!buffer.push(i))
			{
				std::this_thread::yield();
			}
		}
	});

	std::thread consumer([&]() {
		for (int i = 0; i < count; ++i)
		{	
			int value;
			while (!buffer.pop(value))
			{
				std::this_thread::yield();
			}

			sum += value;
		}
	});

	producer.join();
	consumer.join();

	auto finish = std::chrono::steady_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

	std::cout << "time: " << ms << "ms ";
	std::cout << "sum: " << sum << std::endl;
}

int
main(void)
{
	while (true) {
		test();
	}

	return (0);
}