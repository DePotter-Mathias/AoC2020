#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream> //std::stringstream
#include <regex>

using namespace std;

int main()
{
	std::ifstream infile( "day4input.txt" );

	unsigned valid_passes_part1 = 0;
	unsigned valid_passes_part2 = 0;
	{
		std::stringstream strStream;
		strStream << infile.rdbuf(); //read the file
		std::string str = strStream.str(); //str holds the content of the file

		const vector<string> required_words{ "byr","iyr","eyr","hgt","hcl","ecl","pid" /*,"cid" */ };

		const vector<string> regex_rules{
				"byr:(19[2-9][0-9]|200[0-2])",
				"iyr:(201[0-9]|2020)",
				"eyr:(202[0-9]|2030)",
				"hgt:((1[5-8][0-9]|19[0-3])cm|(59|6[0-9]|7[0-6])in)",
				"hcl:#[0-9a-f]{6}",
				"ecl:(amb|blu|brn|gry|grn|hzl|oth)",
				"pid:([0-9]{9}\\b)"
		};

		auto validate_data = [&required_words,&regex_rules]( const string& str )
		{
			return std::all_of( regex_rules.cbegin(), regex_rules.cend(), [&str]( const string& regex ) { return std::regex_search( str, std::regex( regex ) ); } );
		};

		string::size_type previous_location = 0;
		string::size_type current_location = 0;

		while ( true )
		{
			current_location = str.find( "\n\n", current_location + 2 );

			const auto temp_str = str.substr( previous_location, current_location - previous_location );

			if ( std::all_of( required_words.cbegin(), required_words.cend(), [&temp_str]( const string& s ) { return temp_str.find( s ) != string::npos; } ) )
			{
				++valid_passes_part1;

				if ( validate_data( temp_str ) )
				{
					++valid_passes_part2;
				}
			}

			previous_location = current_location;

			if ( current_location == string::npos )
			{
				break;
			}
		}
	}

	//part 1
	{
		cout << "part 1 result: " << valid_passes_part1 << endl;
	}

	//part2
	{
		cout << "part 1 result: " << valid_passes_part2 << endl;
	}
}