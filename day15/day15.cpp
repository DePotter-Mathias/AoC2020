#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

vector<unsigned> read_file_as_vector( stringstream& ss, const char delimiter = '\n' )
{
	vector<unsigned> tokens;
	string token;
	while ( getline( ss, token, delimiter ) )
	{
		tokens.push_back( stoul( token ) );//stoul vs stoi
	}
	return move( tokens );
}

unsigned memory_game( const vector<unsigned> &input, const unsigned number_to_find )
{
	unordered_map<unsigned, unsigned> numbers_visited;

	for ( unsigned i = 0; i < input.size() - 1; ++i )
	{
		numbers_visited[input[i]] = i;
	}

	unsigned f = input.back();
	unsigned next_f;

	for ( auto i = unsigned( input.size() - 1 ); i < number_to_find - 1; ++i )
	{
		const bool found = numbers_visited.count( f ) != 0;
		next_f = found ? i - numbers_visited[f] : 0;
		numbers_visited[f] = i;
		f = next_f;
	}

	return f;
}

int main()
{
	std::ifstream infile( "day15input.txt" );
	stringstream ss;
	ss << infile.rdbuf();
	const auto input = read_file_as_vector( ss, ',' );
	infile.close();

	//part 1
	cout << memory_game( input, 2020 ) << endl;
	//part 1
	cout << memory_game( input, 30000000 ) << endl;
}