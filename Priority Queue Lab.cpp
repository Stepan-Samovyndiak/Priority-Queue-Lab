#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> elements;
    std::function<double(const T&)> priorityFunc;

    void sortQueue() {
        std::sort(elements.begin(), elements.end(),
                  [this](const T& a, const T& b) {
                      return priorityFunc(a) < priorityFunc(b);
                  });
    }

public:
    PriorityQueue(std::function<double(const T&)> func)
        : priorityFunc(func) {}

    void push(const T& element) {
        elements.push_back(element);
        sortQueue();
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("Priority queue is empty.");
        }

        T highestPriority = elements.back();
        elements.pop_back();
        return highestPriority;
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Priority queue is empty.");
        }

        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

int main() {
    PriorityQueue<std::string> pq([](const std::string& s) {
        return static_cast<double>(s.length());
    });

    pq.push("one");
    pq.push("three");
    pq.push("seventeen");
    pq.push("hi");

    std::cout << "Elements popped in priority order:\n";

    while (!pq.empty()) {
        std::cout << pq.pop() << std::endl;
    }

    return 0;
}