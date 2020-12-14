#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

enum class Op
{
	acc,
	jmp,
	nop
};

struct Instruction
{
	Op op = Op::nop;
	signed short int num = 0;
	//bool ran_once = false;
	Instruction( Op o, signed short int n ) : op( o ), num( n )/*, ran_once( false )*/{};

	//bool operator==( const Instruction& lhs, const Instruction& rhs )
	//{
	//	return lhs.num == rhs.num && lhs.op == rhs.op;
	//}
};

int main()
{
	std::ifstream infile( "day8input.txt" );

	vector<Instruction> instructions;
	vector<size_t> instructions_nopjmp;
	size_t index = 0;
	string op_read;
	Op operator_ = Op::nop;

	signed short int num_read;
	while ( ++index, infile >> op_read >> num_read )
	{
		if ( op_read == "acc" )
		{
			operator_ = Op::acc;
		}
		else if ( op_read == "jmp" )
		{
			operator_ = Op::jmp;
			instructions_nopjmp.push_back( index );
		}
		else if ( op_read == "nop" )
		{
			operator_ = Op::nop;
			instructions_nopjmp.push_back( index );
		}
		instructions.emplace_back( operator_, num_read );
		
	}
	infile.close();

	const auto check = [&instructions]( const size_t op_flip = (size_t)-1 )
	{
		size_t accumulation = 0;
		bool looped = true;
		unordered_set<size_t> indeces_executed;

		for ( size_t i = 0; i < instructions.size(); ++i )
		{
			auto in = instructions[i];//searched for hours, had auto& instead of just auto; 

			if ( indeces_executed.count( i ) )
			{
				looped = false;
				break;
			}
			indeces_executed.insert( i );

			if ( op_flip != (size_t)-1 && i == op_flip )
			{
				if ( in.op == Op::nop )
				{
					in.op = Op::jmp;
				}
				else if ( in.op == Op::jmp )
				{
					in.op = Op::nop;
				}
			}

			switch ( in.op )
			{
				/*case  Op::nop :
					break;*/
			case  Op::acc:
				accumulation += in.num;
				break;
			case  Op::jmp:
				i += in.num;
				--i;
				break;
			}
			continue;
		}
		return pair<size_t, size_t>( accumulation, looped );
	};

	//part 1
	{
		cout << "part 1 result: " << check().first << endl;
	}

	size_t result_part_2 = 0;

	for ( size_t index : instructions_nopjmp )
	{
		const auto& result = check( index );
		if ( result.second )
		{
			result_part_2 = result.first;
			break;
		}
	}

	//part2
	{
		cout << "part 2 result: " << result_part_2 << endl;
	}
}