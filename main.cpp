#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

namespace mystl
{
template <class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last,
                    const T& val)
{
    while (first != last)
    {
        if (*first == val) {
            return first;
        }
        ++first;
    }
    return last;
}
template <class ForwardIt, class T>
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    for (; first != last; ++first) {
        *first = value;
    }
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
                    OutputIterator result)
{
    while (first != last) {
        *result++ = *first++;
    }
    return result;
}

template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator result)
{
    while (first != last) {
        *result++ = *--last;
    }
    return result;
}

template<class RandomIt, class RandomFunc>
void random_shuffle(RandomIt first, RandomIt last, RandomFunc&& r)
{
    typename std::iterator_traits<RandomIt>::difference_type i, n;
    n = last - first;
    for (i = n - 1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[r(i + 1)]);
    }
}
}

int main()
{
    std::vector<int> data(10);

    mystl::fill(data.begin(), data.end(), 5);

    *std::prev(data.end()) = 1;

    std::cout << "Found 1 at: " << std::distance(data.begin(), mystl::find(data.begin(), data.end(), 1)) << std::endl;

    std::vector<std::string> dataStrings {
        "hello",
        "stl",
        "c++"
    };

    std::vector<std::string> dataStringsToMoveIn;
    auto insertIterator = std::back_inserter(dataStringsToMoveIn);
    mystl::copy(std::make_move_iterator(dataStrings.begin()),
                std::make_move_iterator(dataStrings.end()),
                insertIterator);
    std::cout << "Size after copying: " << dataStrings.size() << " and " << dataStringsToMoveIn.size() << std::endl;

    auto randomizer = [](const size_t max) {
        return std::rand() % max; // please do not use it
    };
    mystl::random_shuffle(dataStringsToMoveIn.begin(), dataStringsToMoveIn.end(), randomizer);

    std::cout << "After shuffle: " << std::endl;
    for (const auto& entry : dataStringsToMoveIn) {
        std::cout << entry << std::endl;
    }
    return 0;
}
