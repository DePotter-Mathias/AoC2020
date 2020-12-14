#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int main()
{
	std::ifstream infile( "day5input.txt" );
	const vector<pair<unsigned, unsigned>> seats;

	string line;//to capture unwanted data

	unsigned highest_seat = 0;

	const auto get_seat_id = []( string& s )
	{
		unsigned result_row = 0;
		unsigned result_column = 0;

		replace( s.begin(), s.end(), 'B', '1' );
		replace( s.begin(), s.end(), 'F', '0' );
		replace( s.begin(), s.end(), 'R', '1' );
		replace( s.begin(), s.end(), 'L', '0' );
		result_row = stoi( s.substr( 0, 7 ), nullptr, 2 );
		result_column = stoi( s.substr( 7, 3 ), nullptr, 2 );
		return result_row * 8 + result_column;
	};
	vector<unsigned> seat_ids;
	while ( infile >> line )
	{
		const unsigned seat_id = get_seat_id( line );
		if ( highest_seat < seat_id )
		{
			highest_seat = seat_id;
		}
		seat_ids.push_back( seat_id );
	}
	infile.close();

	//part 1
	{
		cout << "part 1 result: " << highest_seat << endl;
	}

	//part2
	{
		sort( seat_ids.begin(), seat_ids.end() );
		const unsigned my_seat = 1 + *adjacent_find( seat_ids.cbegin(), seat_ids.cend(), []( const unsigned a, const unsigned b ) { return a == b - 2; } );
		cout << "part 2 result: " << my_seat << endl;
	}
}