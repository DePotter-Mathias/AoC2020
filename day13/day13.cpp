#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>


using namespace std;

vector<string> read_file_as_vector( stringstream& ss, const char delimiter = '\n' )
{
	vector<string> tokens;
	string token;
	while ( getline( ss, token, delimiter ) )
	{
		tokens.push_back( token );
	}
	return move( tokens );
}

//https://github.com/Chrinkus/advent-of-code-2020/blob/main/src/day13.cpp
//all prop to Chrinkus
//slight alterations made
auto win_contest( const std::vector<unsigned>& buses )
{
	struct Boff
	{
		unsigned val = 0;
		unsigned off = 0;
	};
	vector<Boff> boffs;

	for ( size_t i = 0; i < buses.size(); ++i )
	{
		if ( buses[i] != (unsigned)-1 )//skip the x 's
		{
			boffs.push_back( { buses[i], (unsigned)i } );
		}
	}

	size_t curr_timestamp = 0;
	size_t jump = 1;
	for ( const Boff& boff : boffs )
	{
		while ( (curr_timestamp + boff.off) % boff.val != 0 )
		{
			curr_timestamp += jump;
		}
		jump *= boff.val;
	}

	return curr_timestamp;
}

int main()
{
	std::ifstream infile( "day13input.txt" );
	stringstream ss;
	ss << infile.rdbuf();
	infile.close();

	string s;
	getline( ss, s );
	const unsigned timestamp = stoi( s );
	const auto& shuttles_string = read_file_as_vector( ss, ',' );

	vector<unsigned> shuttles;
	for_each( shuttles_string.cbegin(), shuttles_string.cend(), [&shuttles]( const string& str ) { if ( str != "x" ) { shuttles.emplace_back( stoi( str ) ); } else { shuttles.emplace_back( -1 ); } } );

	//896,915,841,102,983
	//100,000,000,000,000
	//part 1
	{
		const auto shuttle_id =
			*min_element( shuttles.cbegin(), shuttles.cend(),
						  [&timestamp]( const unsigned t1, const unsigned t2 ) { return (t1 - timestamp % t1) < (t2 - timestamp % t2); } );

		//get the next multiple
		const unsigned nearest_shuttle_timestamp = shuttle_id * (timestamp / shuttle_id + 1);
		const unsigned waiting_time = nearest_shuttle_timestamp - timestamp;

		cout << "part 1 result: " << shuttle_id * waiting_time << endl;
	}

	//part2
	{
		const auto sol = win_contest( shuttles );
		cout << "part 2 result: " << sol << endl;
	}
}