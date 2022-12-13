//
// Created by LMR on 2022/12/12.
// 洗牌函数 打乱顺序
//

#ifndef RANDOMSHUFFLE_H
#define RANDOMSHUFFLE_H
#include <chrono>
#include <random>

template<class RandomIt>
void RandomShuffle(RandomIt first, RandomIt last)
{
	using diff_t = typename std::iterator_traits<RandomIt>::difference_type;
	using distr_t = std::uniform_int_distribution<diff_t>;
	using param_t = typename distr_t::param_type;

	distr_t D;
	std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());

	diff_t n = last - first;
	for (diff_t i = n - 1; i > 0; --i) {
		using std::swap;
		swap(first[i], first[D(e, param_t(0, i))]);
	}
}

template<class RandomIt, class RandomFunc>
void RandomShuffle(RandomIt first, RandomIt last, RandomFunc &&randomFunc)
{
	typename std::iterator_traits<RandomIt>::difference_type i, n;
	n = last - first;
	for (i = n - 1; i > 0; --i) {
		using std::swap;
		std::swap(first[i], first[randomFunc(i + 1)]);
	}
}



#endif //RANDOMSHUFFLE_H
