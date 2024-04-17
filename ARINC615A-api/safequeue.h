#pragma once
#include<queue>
#include<mutex>
template <typename T>
class SafeQueue {
public:
	SafeQueue(){}
	SafeQueue(SafeQueue &&other){}
	~SafeQueue(){}

	bool empty() const {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}

	int size() const {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.size();
	}

	void enqueue(T&& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.emplace(std::forward<T>(t));
	}

	bool dequeue(T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty()) return false;
		t = std::move(m_queue.front());
		m_queue.pop();
		return true;
	}
private:
	std::queue<T> m_queue;
	mutable std::mutex m_mutex;
};
