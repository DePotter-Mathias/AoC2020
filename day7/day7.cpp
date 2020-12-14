#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iomanip>
#include <unordered_set>

using namespace std;

const unsigned count_bags( const map<string, vector<pair<unsigned, string>>>& bags, const string& bag_colour )
{
	unsigned count_inside = 1;
	for ( auto inside : bags.at( bag_colour ) )
	{
		if ( bags.count( inside.second ) == 0 )
		{
			continue;
		}
		count_inside += inside.first * count_bags( bags, inside.second );
	}
	return count_inside;
};


int main()
{
	std::ifstream infile( "day7input.txt" );
	std::stringstream strStream;
	strStream << infile.rdbuf(); //read the file
	std::string str = strStream.str(); //str holds the content of the file

	const string string_at_end_of_bag_name{ " bags contain" };

	//vector<string> bags_to_search( { "shiny gold" } );

	//for ( ;;)
	//{
	//	auto found_bag_pos = string::npos;
	//	for ( const string& to_find : bags_to_search )
	//	{
	//		if ( found_bag_pos = str.find( " " + to_find ), found_bag_pos != string::npos )
	//		{
	//			break;
	//		}
	//	}
	//	if ( found_bag_pos == string::npos )
	//	{
	//		break;
	//	}

	//	//no need to check if found or not,
	//	//npos = (size_type)-1;, so adding +1 makes npos + 1 == 0; AKA first char of string
	//	//and because this is a rfind (reverse find) we can only worst case start at 0
	//	//move one over, now points to first letter of bag name
	//	const auto bag_colour_start = str.rfind( '\n', found_bag_pos ) + 1;
	//	const auto bag_colour_end = str.find( string_at_end_of_bag_name, bag_colour_start );
	//	if ( bag_colour_end == string::npos )
	//	{
	//		throw;//but should never happen !
	//	}

	//	const string& bag_name = str.substr( bag_colour_start, bag_colour_end - bag_colour_start );
	//	bags_to_search.push_back( bag_name );

	//	str.erase( bag_colour_start - 1, str.find( '\n', bag_colour_start ) - bag_colour_start + 1 );
	//}

	//we assume no bag-loops (e.g. shiny gold bag nested inside shiny gold bag)
	map<string, vector<pair<unsigned, string>>> bags;

	for ( ;;)
	{
		const auto bag_name_end = str.find( string_at_end_of_bag_name );
		if ( bag_name_end == string::npos )
		{
			break;
		}

		const string& bag_name = str.substr( 0, bag_name_end );

		const auto from = bag_name_end + string_at_end_of_bag_name.length();
		const auto to = str.find( '.', from );
		const string& bag_content = str.substr( from, to - from );

		stringstream ss( bag_content );
		string bag;
		while ( getline( ss, bag, ',' ) )
		{
			bag.erase( bag.find( " bag" ) );
			bags[bag_name].push_back( { bag[1] - '0', bag.substr( 3 ) } );
		}

		str.erase( 0, to + 2 );
	}

	unordered_set<string> bags_to_search{ {"shiny gold"} };
	unsigned change = 0;
	unsigned before = 0;
	do
	{
		change = before;
		std::for_each( bags.cbegin(), bags.cend(),
					   [&bags_to_search]( const auto in )
					   {
						   const auto c = find_first_of( in.second.cbegin(), in.second.cend(), bags_to_search.cbegin(), bags_to_search.cend(), []( const auto& a, const auto& b ) { return b == a.second; } );
						   if ( c != in.second.cend() )
						   {
							   bags_to_search.insert( in.first );
						   }
					   } );
		before = bags_to_search.size();
	}
	while ( change != before );


	//part 1
	{
		cout << "part 1 result: " << bags_to_search.size() - 1 << endl;
	}

	//part2
	{
		cout << "part 2 result: " << count_bags( bags, "shiny gold" ) - 1 << endl;
	}
}