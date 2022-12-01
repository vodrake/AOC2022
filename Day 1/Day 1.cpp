// Day 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>

int main()
{
	std::vector<int32_t> calorie_lines;
	std::string line;
	std::vector<std::pair<int32_t, int32_t> > elf_array;

	std::ifstream input_file( "input.txt" );
	if ( input_file.is_open() )
	{
		while ( std::getline( input_file, line ) )
		{
			if ( !line.empty() )
			{
				//build our vector of depths from the input
				calorie_lines.push_back( std::stoi( line ) );
			}
			else
			{
				//add a 0 to indicate we're moving to the next elf
				calorie_lines.push_back( 0 );
			}
		}

		int current_elf_idx = 0;
		int current_elf_calories = 0;


		auto process_current_elf = [&]()
		{
			elf_array.push_back( { current_elf_idx + 1, current_elf_calories } );
			current_elf_idx++;
			current_elf_calories = 0;
		};


		for ( size_t food_idx = 0; food_idx < calorie_lines.size(); ++food_idx )
		{
			const int32_t food_item = calorie_lines[food_idx];

			current_elf_calories += food_item;

			//if new elf
			if ( food_item == 0 || food_idx == calorie_lines.size() - 1 )
			{
				process_current_elf();
			}
		}

		//sort our elves by calories (most calories first)
		std::sort( elf_array.begin(), elf_array.end(), []( auto& elf_a, auto& elf_b )
				   {
					   return elf_a.second > elf_b.second;
				   } );
	}

	if ( !elf_array.size() )
	{
		std::cout << "Somethings gone wrong. We have no elves!" << std::endl;
		return 0;
	}
	//----------------------------------------------------------------------------
	//------------------------------ PART 1---------------------------------------
	//----------------------------------------------------------------------------
	std::cout << "=================PART 1=========================" << std::endl;
	std::cout << "Elf with Most calories: " << elf_array[0].first << " Most calories : " << elf_array[1].second << std::endl;

	//----------------------------------------------------------------------------
	//------------------------------ PART 2---------------------------------------
	//----------------------------------------------------------------------------

	std::cout << "=================PART 2=========================" << std::endl;
	int32_t top_three_calories = 0;
	for ( size_t idx = 0; idx < std::min((size_t)3, elf_array.size()); ++idx )
	{
		top_three_calories += elf_array[idx].second;
	}

	std::cout <<  "Top 3 Most calories sum : " << top_three_calories << std::endl;
}

