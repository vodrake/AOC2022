// Day 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>


constexpr bool IS_PART_B = true;

enum SHAPE : int32_t
{
	INVALID = 0,
	ROCK = 1,
	PAPER = 2,
	SCISSORS = 3
};

int32_t get_score( const SHAPE& my_shape, const SHAPE& opp_shape )
{
	if ( (my_shape == ROCK && opp_shape == SCISSORS) ||
		 (my_shape == SCISSORS && opp_shape == PAPER) ||
		 (my_shape == PAPER && opp_shape == ROCK) )
	{
		return 6;
	}
	else if ( my_shape == opp_shape )
	{
		return 3;
	}

	return 0;

}

SHAPE get_shape_from_string_part_b( const std::string& shape_str, const SHAPE& opp_shape )
{
	//x = find the losing shape
	//y = find the drawing shape
	//z = find the winning shape

	const char* shape_char = shape_str.c_str();
	int32_t score_to_test_against = 0;

	switch ( shape_char[0] )
	{
	case 'Y':
		score_to_test_against = 3;
		break;;
	case 'Z':
		score_to_test_against = 6;
		break;
	};

	for ( int32_t test_shape = ROCK; test_shape <= SCISSORS; ++test_shape )
	{
		if ( get_score( static_cast<SHAPE>(test_shape), opp_shape ) == score_to_test_against )
		{
			return static_cast<SHAPE>(test_shape);
		}
	}
	return INVALID;
}


SHAPE get_shape_from_string( const std::string& shape_str )
{
	const char* shape_char = shape_str.c_str();
	switch ( shape_char[0] )
	{
	case 'A':
	case 'X':
		return ROCK;
	case 'B':
	case 'Y':
		return PAPER;
	case 'C':
	case 'Z':
		return SCISSORS;

	};
	return INVALID;
}



int32_t get_my_score_from_shapes( const std::string& my_shape_str, const std::string& opp_shape_str )
{
	const SHAPE& opp_shape = get_shape_from_string( opp_shape_str );
	const SHAPE& my_shape = IS_PART_B ? get_shape_from_string_part_b(my_shape_str, opp_shape ) : get_shape_from_string(my_shape_str);
	return get_score( my_shape, opp_shape ) + static_cast<int32_t>(my_shape);
}


int main()
{
	std::vector<int32_t> score_lines;
	std::string line;

	int32_t total = 0;
	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		while ( std::getline( input_file, line ) )
		{
			if ( !line.empty() )
			{
				std::istringstream iss( line );

				const std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

				total += get_my_score_from_shapes( tokens[1], tokens[0] );
			}
		}
	}

	//----------------------------------------------------------------------------
	//------------------------------ PART 1 & 2---------------------------------------
	//----------------------------------------------------------------------------
	std::cout << "=================PART 1=========================" << std::endl;
	std::cout << "My score: " << total << std::endl;

}