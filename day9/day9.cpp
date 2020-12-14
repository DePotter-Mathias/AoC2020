#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

constexpr unsigned preamble{ 25 };

int main()
{
	std::ifstream infile( "day9input.txt" );
	const std::istream_iterator<unsigned> start( infile ), end;
	vector<unsigned> numbers( start, end );

	const auto sum_finder = [&numbers]( const size_t i )
	{
		const auto num_to_find = numbers[i];
		for ( size_t j = i - preamble; j < i; ++j )
		{
			const auto num_at_j = numbers[j];
			for ( size_t k = j; k < i; ++k )
			{
				const auto num_at_k = numbers[k];
				if ( num_at_j + num_at_k == num_to_find )
				{
					return true;
				}
			}
		}
		return false;
	};

	const auto contigious_sum_finder = [&numbers]( const size_t number_to_find )
	{
		const auto numbers_size = numbers.size();
		for ( size_t i = 0; i < numbers_size; ++i )
		{
			unsigned current_sum = 0;

			for ( size_t j = i; j < numbers_size; ++j )
			{
				current_sum += numbers[j];
				if ( current_sum > number_to_find )
				{
					break;
				}
				if ( current_sum == number_to_find )
				{
					//again wasted so much time, min_max has an exclusive end without telling me >:(
					const auto p = std::minmax_element( numbers.cbegin() + i, numbers.cbegin() + j + 1 );
					return *p.first + *p.second;
				}
			}
		}
		return (unsigned)0;
	};

	unsigned result_part1 = 0;
	unsigned result_part2 = 0;

	for ( size_t i = preamble; i < numbers.size(); ++i )
	{
		if ( !sum_finder( i ) )
		{
			result_part1 = numbers[i];
			result_part2 = contigious_sum_finder( numbers[i] );
			break;
		}
	}

	//part 1
	{
		cout << "part 1 result: " << result_part1 << endl;
	}

	//part2
	{
		cout << "part 1 result: " << result_part2 << endl;
	}
}