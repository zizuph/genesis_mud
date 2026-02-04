/*
    This is a standard east road. Mortricia 920723
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)

create_room()
{
    set_short("A small path");

    set_long(BS(
        "This icy path takes you eastwards, deeper and darker into " +
        "the forest.  You hear the voices of many people, all singing " +
        "a song, in some evil sounding language, coming from the east.  " +
        "You feel drawn towards it.  The " +
        "path leads to a castle, to your southeast, where the music seems " +
        "to be coming from, or back towards the road to the west.\n"));

    add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
        "straight. Perfect for building cabins and houses.\n"));

    add_item(({"snow"}), BS("The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n"));

    
    add_exit(TOWNDIR + "road_s/p_guild_4", "west", 0);
    add_exit("/d/Terel/minstrels/dark/outside", "southeast", 0);

}
