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
	for_each( shuttles_string.cbegin(), shuttles_string.cend(), [&shuttles]( const string& str ) { if ( str != "x" ) { shuttles.emplace_back( stoi( str ) ); } } );



	unsigned t = timestamp;

	find_if( shuttles.cbegin(), shuttles.cend(),
			 [&shuttles]( const unsigned s )
			 {
				 return 
			 } );
	//

		//896,915,841,102,983
		//100,000,000,000,000
		//part 1
	{
		const auto shuttle_id =
			*min_element( shuttles.cbegin(), shuttles.cend(),
						  [&timestamp]( const unsigned t1, const unsigned t2 ) { return (t1 - timestamp % t1) < (t2 - timestamp % t2); } );

		const unsigned nearest_shuttle_timestamp = (shuttle_id * (timestamp / shuttle_id + 1));
		const unsigned waiting_time = nearest_shuttle_timestamp - timestamp;

		cout << "part 1 result: " << shuttle_id * waiting_time << endl;
	}

	//part2
	{
		//cout << "part 2 result: " << count_part2 << endl;
	}
}