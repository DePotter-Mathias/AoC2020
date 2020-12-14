#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <sstream> //std::stringstream
#include <tuple>

using namespace std;

vector<string> read_file_as_vector( const string& file_name, const char delimiter = '\n' )
{
	vector<string> tokens;
	ifstream infile( file_name );
	string token;
	while ( getline( infile, token, delimiter ) )
	{
		tokens.push_back( token );
	}
	infile.close();
	return move( tokens );
}

constexpr char floor_space = '.';
constexpr char seat_free = 'L';
constexpr char seat_taken = '#';

struct Seat_Position
{
	signed char x = 0;
	signed char y = 0;
};

//anon struct
constexpr Seat_Position three_by_three[]{
	{-1,-1},	{0,-1},		{1,-1},
	{-1,0 }	 /*,{0,0 }*/,	{1,0 },
	{-1,1 },	{0,1 },		{1,1 }
};

namespace
{
	static size_t g_file_width = 0;
	static size_t g_file_height = 0;
}

auto count_taken_seats_around( const size_t x, const size_t y, const vector<string>& arr )
{
	return count_if( cbegin( three_by_three ), cend( three_by_three ), [&]( const Seat_Position& off )
					 {
						 if ( off.x + x < 0 || off.x + x >= g_file_height || off.y + y < 0 || off.y + y >= g_file_width )
						 {
							 return false;
						 }
						 return arr[x + off.x][y + off.y] == seat_taken;
					 } );
}

unsigned count_taken_seats( const vector<string>& arr )
{
	const auto h = arr.size();
	unsigned c = 0;
	for ( size_t i = 0; i < g_file_height; ++i )
	{
		for ( size_t j = 0; j < g_file_width; ++j )
		{
			c += (arr[i][j] == seat_taken);
		}
	}
	return c;
}

int main()
{
	const auto input_vec = read_file_as_vector( "day11input.txt" );
	g_file_width = input_vec[0].length();
	g_file_height = input_vec.size();

	auto old_vec = input_vec;
	do
	{
		auto new_vec = old_vec;

		bool changed = false;
		for ( size_t i = 0; i < g_file_height; ++i )
		{
			for ( size_t j = 0; j < g_file_width; ++j )
			{
				if ( old_vec[i][j] == seat_free )
				{
					if ( count_taken_seats_around( i, j, old_vec ) == 0 )
					{
						new_vec[i][j] = seat_taken;
						changed = true;
					}
				}
				else if ( old_vec[i][j] == seat_taken )
				{
					if ( count_taken_seats_around( i, j, old_vec ) >= 4 )
					{
						new_vec[i][j] = seat_free;
						changed = true;
					}
				}
			}
		}
		if ( !changed )
		{
			break;
		}
		old_vec = new_vec;
	}
	while ( true );

	//part 1
	{
		cout << "part 1 result: " << count_taken_seats( old_vec ) << endl;
	}

	//part2
	{
		//cout << "part 2 result: " << result_part2 << endl;
	}
}