#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <corecrt_math_defines.h>

using namespace std;

struct Instruction
{
	char command = ' ';
	unsigned quantity = 0;
};

struct PositionAngle
{
	int x = 0;
	int y = 0;
	int angle = 0;

	const int Manhattan_distance() const
	{
		return abs( x ) + abs( y );
	}
};

constexpr double rad_to_deg = M_PI / 180;

void Rotate_Point( PositionAngle& p, const int angle )
{
	//int p_angle = abs(angle) > 180 ? angle % 180 : angle;
	//we know s and c will be withing the range: ]-1,1[
	//and we don't need more precision than 90 degree angles
	const int s = static_cast<int>(sin( angle * rad_to_deg ));
	const int c = static_cast<int>(cos( angle * rad_to_deg ));

	const int xnew = p.x * c + p.y * s;
	const int ynew = p.y * c - p.x * s;

	p.x = xnew;
	p.y = ynew;
	p.angle = 0;
}

int main()
{
	std::ifstream infile( "day12input.txt" );
	Instruction input;

	PositionAngle boat1;

	PositionAngle waypoint{ 10,1 };
	PositionAngle boat2;

	while ( infile >> input.command >> input.quantity )
	{
		// part 1
		{
			switch ( input.command )
			{
			case 'N':
				boat1.y += input.quantity;
				break;
			case 'E':
				boat1.x += input.quantity;
				break;
			case 'S':
				boat1.y -= input.quantity;
				break;
			case 'W':
				boat1.x -= input.quantity;
				break;
			case 'L':
				boat1.angle -= input.quantity;
				break;
			case 'R':
				boat1.angle += input.quantity;
				break;
			case 'F':
				boat1.x += static_cast<int>(cos( boat1.angle * rad_to_deg ) * input.quantity);
				boat1.y -= static_cast<int>(sin( boat1.angle * rad_to_deg ) * input.quantity);
				break;
			}
		}

		// part 2
		{
			switch ( input.command )
			{
			case 'N':
				waypoint.y += input.quantity;
				break;
			case 'E':
				waypoint.x += input.quantity;
				break;
			case 'S':
				waypoint.y -= input.quantity;
				break;
			case 'W':
				waypoint.x -= input.quantity;
				break;
			case 'L':
				Rotate_Point( waypoint, -(int)input.quantity );
				break;
			case 'R':
				Rotate_Point( waypoint, input.quantity );
				break;
			case 'F':
				boat2.x += waypoint.x * input.quantity;
				boat2.y += waypoint.y * input.quantity;
				break;
			}
		}
	}
	//part 1
	{
		cout << "part 1 result: " << boat1.Manhattan_distance() << endl;
	}

	//part2
	{
		cout << "part 2 result: " << boat2.Manhattan_distance() << endl;
	}
}