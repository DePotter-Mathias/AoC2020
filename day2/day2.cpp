#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct data_structure
{
	unsigned mini = 0;
	unsigned maxy = 0;
	char letter = ' ';
	string password;
};

bool check_data_structure_password_part1( const data_structure& ds )
{
	const auto occurences = std::count( ds.password.cbegin(), ds.password.cend(), ds.letter );
	return occurences >= ds.mini && occurences <= ds.maxy;
}

bool check_data_structure_password_part2( const data_structure& ds )
{
	//short c = 0;
	//if (ds.password[ds.mini-1] == ds.letter)
	//{
	//	++c;
	//}
	//if (ds.password[ds.maxy-1] == ds.letter)
	//{
	//	++c;
	//}
	//return c == 1;
	//Matt While's idea
	return (ds.password[ds.mini - 1] == ds.letter) ^ (ds.password[ds.maxy - 1] == ds.letter);
}

int main()
{
	std::ifstream infile( "day2input.txt" );
	data_structure ds;
	char trash;//to capture unwanted data

	unsigned count_part1 = 0;
	unsigned count_part2 = 0;

	while ( infile >> ds.mini >> trash >> ds.maxy >> ds.letter >> trash >> ds.password )
	{
		if ( check_data_structure_password_part1( ds ) )
		{
			++count_part1;
		}
		if ( check_data_structure_password_part2( ds ) )
		{
			++count_part2;
		}
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