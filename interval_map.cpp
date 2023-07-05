#include<iostream>
#include<list>
#include<map>

template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
    interval_map(V const& val)
            : m_valBegin(val)
    {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd)) {
            return; // Empty interval, do nothing
        }

        auto next = m_map.upper_bound(keyBegin);

        auto prev = m_map.end();
        if (next == m_map.begin()) {
            prev = m_map.end();
        } else {
            prev = std::prev(next);
        }

        if (prev != m_map.end() && prev->second == val) {
            return; // No need to make any changes if the previous value is the same as val
        }

        if (prev != m_map.end() && prev->second == m_valBegin) {
            m_map.erase(prev); // Remove the previous element if its value is the same as m_valBegin
            prev = (next == m_map.begin()) ? m_map.end() : std::prev(next);
        }

        if (next != m_map.end() && next->second == val) {
            return; // No need to make any changes if the next value is the same as val
        }

        if (prev != m_map.end() && prev->second == val) {
            prev->first = keyEnd; // Update the key to keyEnd if the previous value is the same as val
        }
        else {
            m_map.emplace_hint(next, std::make_pair(keyBegin, val)); // Insert a new element representing the interval [keyBegin, keyEnd) with the value val
        }
    }


    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        }
        else {
            return std::prev(it)->second;
        }
    }
};








// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

void runIntervalMapTests() {
    interval_map<int, char> M('A');
    M.assign(1, 3, 'B');
    M.assign(5, 7, 'C');
    M.assign(-5, -3, 'D');
    M.assign(0, 10, 'E');
    M.assign(2, 6, 'F');

    // Expected output:
    // -10 -> 'A'
    // -9 -> 'A'
    // ...
    // -4 -> 'A'
    // -3 -> 'D'
    // -2 -> 'A'
    // -1 -> 'A'
    // 0 -> 'E'
    // 1 -> 'B'
    // 2 -> 'F'
    // 3 -> 'F'
    // 4 -> 'F'
    // 5 -> 'F'
    // 6 -> 'F'
    // 7 -> 'C'
    // 8 -> 'C'
    // 9 -> 'C'
    // ...
    std::cout << "Printing interval_map M:\n";
    for (int i = -10; i <= 10; ++i) {
        std::cout << i << " -> " << M[i] << '\n';
    }
    std::cout << '\n';

    // Additional test cases
    M.assign(-7, -2, 'G');
    M.assign(4, 8, 'H');

    // Expected output:
    // -10 -> 'A'
    // -9 -> 'A'
    // ...
    // -8 -> 'G'
    // -7 -> 'G'
    // -6 -> 'G'
    // -5 -> 'G'
    // -4 -> 'G'
    // -3 -> 'D'
    // -2 -> 'G'
    // -1 -> 'A'
    // 0 -> 'E'
    // 1 -> 'B'
    // 2 -> 'F'
    // 3 -> 'F'
    // 4 -> 'H'
    // 5 -> 'H'
    // 6 -> 'H'
    // 7 -> 'H'
    // 8 -> 'C'
    // 9 -> 'C'
    // ...
    std::cout << "Printing interval_map M after additional assignments:\n";
    for (int i = -10; i <= 10; ++i) {
        std::cout << i << " -> " << M[i] << '\n';
    }
    std::cout << '\n';
}


int main() {
    runIntervalMapTests();
    return 0;
};