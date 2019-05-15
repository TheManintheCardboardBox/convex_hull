#pragma once

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <cstddef>
#include <vector>
#include <utility>

namespace lab {

	template <typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
	class priority_queue
	{
	public:
		priority_queue()
			: data(), comp()
		{
		}

		explicit priority_queue(const Compare& pred)
			: data(), comp(pred)
		{
		}

		priority_queue(const Container& cont, const Compare& pred)
			: data(cont), comp(pred)
		{
			build_heap();
		}

		template<class Iterator>
		priority_queue(Iterator first, Iterator last)
			: data(first, last), comp()
		{
			build_heap();
		}

		template<class Iterator>
		priority_queue(Iterator first, Iterator last, const Compare& pred)
			: data(first, last), comp(pred)
		{
			build_heap();
		}

		priority_queue(const priority_queue& other)
			: data(other.data), comp(other.comp)
		{
		}

		priority_queue(priority_queue&& other)
			: data(std::move(other.data)), comp(std::move(other.comp))
		{
		}

		void push(const T& val)
		{
			data.push_back(val);
			heapify(size() - 1);
		}

		void push(T&& val)
		{
			data.push_back(std::move(val));
			heapify(size() - 1);
		}

		bool empty() const
		{
			return data.empty();
		}

		std::size_t size() const
		{
			return data.size();
		}

		const T& top() const
		{
			return data.front();
		}

		void pop()
		{
			std::iter_swap(data.begin(), data.end() - 1);
			data.pop_back();

			heapify(0);
		}

		void swap(priority_queue& other)
		{
			std::swap(data, other.data);
			std::swap(comp, other.comp);
		}

	private:
		Container data;
		Compare comp;

		std::size_t left_child(std::size_t parent)
		{
			return (parent + 1) * 2 - 1;
		}

		std::size_t right_child(std::size_t parent)
		{
			return (parent + 1) * 2;
		}

		std::size_t parent(std::size_t child) const
		{
			return (child - 1) / 2;
		}

		void heapify(std::size_t idx)
		{
			std::size_t left = left_child(idx);
			std::size_t right = right_child(idx);

			std::size_t largest = idx;

			if (left < size() && comp(data[left], data[largest]))
				largest = left;

			if (right < size() && comp(data[right], data[largest]))
				largest = right;

			if (largest != idx) {
				std::iter_swap(data.begin() + idx, data.begin() + largest);
				heapify(largest);
			}
		}

		void build_heap()
		{
			for (std::size_t i = size() / 2 - 1; i < size() / 2; i--)
				heapify(i);
		}
	};

	template <typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
	void swap(priority_queue<T, Container, Compare>& lhs, priority_queue<T, Container, Compare>& rhs)
	{
		lhs.swap(rhs);
	}

} // namespace lab

#endif PRIORITY_QUEUE_HPP
