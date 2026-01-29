/*  
    Randomize ore by value, used in prospecting and mining.
    Original code from: /d/Genesis/gems/gem_manager.c

    Made by: Maelstrom, 2016/01

*/

#include "common.c";

//selects an ore randomly, having less chance to be selected the more valuable it is.
string
random_ore_by_value(int seed)
{
    return random_by_percent(seed, ORES, "rarity");
}