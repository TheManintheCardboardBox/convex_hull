#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <vector>
#include <utility>

namespace lab {

	template <typename T, typename Container = std::vector<T>>
	class stack
	{
	public:
		stack()
			: data()
		{
		}

		explicit stack(const Container& cont)
			: data(cont)
		{
		}

		explicit stack(Container&& cont)
			: data(std::move(cont))
		{
		}

		stack(const stack& other)
			: data(other.data)
		{
		}

		stack(stack&& other)
			: data(std::move(other.data))
		{
		}

		void push(const T& val)
		{
			data.push_back(val);
		}

		void push(T&& val)
		{
			data.push_back(std::move(val));
		}

		void pop()
		{
			data.pop_back();
		}

		bool empty() const
		{
			return data.empty();
		}

		std::size_t size() const
		{
			return data.size();
		}

		T& top()
		{
			return data.back();
		}

		const T& top() const
		{
			return data.back();
		}

		void swap(stack& other)
		{
			std::swap(data, other.data);
		}

	private:
		Container data;
	};

	template <typename T, typename Container = std::vector<T>>
	void swap(stack<T, Container>& lhs, stack<T, Container>& rhs)
	{
		lhs.swap(rhs);
	}

} // namespace lab

#endif STACK_HPP
