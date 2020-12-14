#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int main()
{
	ifstream infile( "day3input.txt" );
	const std::istream_iterator<char> start( infile ), end;
	const vector<char> map( start, end );

	//we still need the map width, no really nice way to do that I guess??
	infile.clear();

	// back to the start!
	infile.seekg( 0, std::ios::beg );

	// read first line of file again
	string line;
	getline( infile, line );

	//how long is that? 31? nice!
	const size_t map_width = line.length();

	//should have integer result anyway, so should be safe
	const size_t map_height = map.size() / map_width;

	const auto count_trees = [&]( const size_t x_offset, const size_t y_offset )
	{
		unsigned tree_count = 0;

		for ( size_t i = 0, j = 0; i + j < map_height + map_width; i += x_offset )
		{
			if ( map[i * map_width + j] == '#' )
			{
				++tree_count;
			}

			j += y_offset;
			j %= map_width;
		}
		return tree_count;
	};

	//part 1
	{
		cout << "part 1 result: " << count_trees( 1, 3 ) << endl;
	}

	//part2
	{
		cout << "part 2 result: "
			<< count_trees( 1, 1 )
			* count_trees( 1, 3 )
			* count_trees( 1, 5 )
			* count_trees( 1, 7 )
			* count_trees( 2, 1 ) << endl;
	}
}