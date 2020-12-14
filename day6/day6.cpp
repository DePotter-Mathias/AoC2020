#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	std::ifstream infile( "day6input.txt" );

	//string group_answers;
	map<char, size_t> answers_map;
	string line;
	size_t count_entries = 0;
	size_t count_part1 = 0;
	size_t count_part2 = 0;

	while ( getline( infile, line, '\n' ) )
	{
		for_each( line.cbegin(), line.cend(), [&answers_map]( const char c ) { ++answers_map[c]; } );

		if ( line.empty() || infile.eof() )
		{
			count_part1 += answers_map.size();
			count_part2 += std::count_if( answers_map.cbegin(), answers_map.cend(), [&count_entries]( const pair<char, size_t>& awnsers ) { return awnsers.second >= count_entries; } );
			
			answers_map.clear();
			count_entries = 0;
			continue;
		}

		++count_entries;
	}

	//part 1
	{
		cout << "part 1 result: " << count_part1 << endl;
	}

	//part2
	{
		cout << "part 2 result: " << count_part2 << endl;
	}
}