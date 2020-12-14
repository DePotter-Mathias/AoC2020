#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
	std::ifstream infile( "day1input.txt" );
	const std::istream_iterator<unsigned int> start( infile ), end;
	const vector<unsigned int> numbers( start, end );
	const unsigned int number_to_find = 2020;

	const auto find_product = [&]( const unsigned int number_to_find, const size_t start_from = 0 )
	{
		vector<unsigned int> numbers_inverse;
		for ( size_t i = start_from; i < numbers.size(); ++i )
		{
			if ( std::find( numbers_inverse.cbegin(), numbers_inverse.cend(), numbers[i] ) != numbers_inverse.cend() )
			{
				return numbers[i];
			}
			numbers_inverse.push_back( number_to_find - numbers[i] );
		}
		return number_to_find + 1;
	};

	//part 1
	{
		const auto result = find_product( number_to_find );
		if ( result != number_to_find + 1 )
		{
			cout << "Part 1 found: " << result << " and " << number_to_find - result << "\nresult: " << result * (number_to_find - result) << endl;
		}
		else
		{
			cout << "Nothing found :( check your code" << endl;
		}
	}

	//part 2
	{
		for ( size_t i = 0; i < numbers.size(); ++i )
		{
			const auto inverted = number_to_find - numbers[i];
			const auto result = find_product( inverted, i + 1 );

			if ( result != inverted + 1 )
			{
				cout << "Part 2 result: " << numbers[i] * result * (number_to_find - (numbers[i] + result)) << endl;
				break;
			}
		}
	}
}

