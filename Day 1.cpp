// Day 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>

const enum DEPTH_CHANGE
{
	SAME,
	DECREASE,
	INCREASE,
	COUNT
};

int main()
{
	std::vector<int32_t> depth_lines;
	std::string line;

	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		while ( std::getline( input_file, line ) )
		{
			if ( !line.empty() )
			{
				//build our vector of depths from the input
				depth_lines.push_back( std::stoi( line ) );
			}
		}
	}


	//----------------------------------------------------------------------------
	//------------------------------ PART 1---------------------------------------
	//----------------------------------------------------------------------------

	using DEPTH_COUNT_ARRAY = std::array<int32_t, DEPTH_CHANGE::COUNT>;

	auto build_change_counts = []( const std::vector<int32_t>& lines )->DEPTH_COUNT_ARRAY
	{
		DEPTH_COUNT_ARRAY change_counts = { 0 };
		for ( size_t idx = 1; idx < lines.size(); ++idx )
		{
			if ( lines[idx] > lines[idx - 1] )
			{
				change_counts[DEPTH_CHANGE::INCREASE]++;
			}
			else if ( lines[idx] < lines[idx - 1] )
			{
				change_counts[DEPTH_CHANGE::DECREASE]++;
			}
			else
			{
				change_counts[DEPTH_CHANGE::SAME]++;
			}
		}
		return change_counts;
	};

	const DEPTH_COUNT_ARRAY& change_counts_one = build_change_counts( depth_lines );
	std::cout << "=================PART 1=========================" << std::endl;
	std::cout << "Number of increases: " << change_counts_one[DEPTH_CHANGE::INCREASE] << std::endl;

	//----------------------------------------------------------------------------
	//------------------------------ PART 2---------------------------------------
	//----------------------------------------------------------------------------

	const int32_t MAX_BOXES_TO_FILL = 3;
	std::vector<int32_t> three_line_depths;
	for ( size_t idx = 0; idx < depth_lines.size(); ++idx )
	{
		//the last 2 numbers will not be able to make 3 groups of 3 due to the nature of how this is build
		const int32_t number_of_groups_can_fill = std::min< int32_t>( MAX_BOXES_TO_FILL, (int32_t)(depth_lines.size() - idx) );

		for ( int32_t snd_idx = (int32_t)idx - (MAX_BOXES_TO_FILL - number_of_groups_can_fill); snd_idx >= 0 && snd_idx > ( int32_t )idx - MAX_BOXES_TO_FILL; --snd_idx )
		{
			if ( three_line_depths.size() <= snd_idx )
			{
				three_line_depths.push_back( depth_lines[idx] );
			}
			else
			{
				three_line_depths[snd_idx] += depth_lines[idx];
			}
			
		}
	}

	const DEPTH_COUNT_ARRAY& change_counts_two = build_change_counts( three_line_depths );
	std::cout << "=================PART 2=========================" << std::endl;
	std::cout << "Number of increases: " << change_counts_two[DEPTH_CHANGE::INCREASE] << std::endl;
}

