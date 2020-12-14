#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

//only works for j between 1 and 4 
size_t Tribonnacci( const size_t j )
{
	return (j * j - j) / 2 + 1;
}

int main()
{
	std::ifstream infile( "day10input.txt" );
	const std::istream_iterator<unsigned> start( infile ), end;
	vector<unsigned> numbers( start, end );

	sort( numbers.begin(), numbers.end() );
	numbers.push_back( numbers.back() + 3 );

	vector<unsigned> diff( numbers.size() );
	adjacent_difference( numbers.cbegin(), numbers.cend(), diff.begin() );

	//part 1
	{
		const auto ones = count( diff.cbegin(), diff.cend(), 1 );
		const auto threes = count( diff.cbegin(), diff.cend(), 3 );

		cout << "part 1 result: " << ones * threes << endl;
	}

	//part2
	{
		//needed larger type than an unsigned int
		size_t result_part2 = 1;

		for ( size_t i = 0, j = 1; i < diff.size() - 1; ++i, ++j )
		{
			if ( diff[i] != diff[i + 1] || diff[i] == 3 || i + 1 == diff.size() )
			{
				result_part2 *= Tribonnacci( j );
				j = 0;
			}
		}

		cout << "part 2 result: " << result_part2 << endl;
	}
}