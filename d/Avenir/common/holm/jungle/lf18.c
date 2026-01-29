// file name:        /d/Avenir/common/holm/jungle/lf18.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_jungle_room()
{
    set_short("natural stone staircase. Track curves northeast, "+
        "south into bushes");
    set_long("You are in the humid embrace of a lowland forest. "+
        "Blocks of basaltic stone form a natural staircase that "+
        "rises out of sight above the forest canopy in the east. "+
        "The ancient track continues northeast into a hollow. "+
        "The thorny bushes which once formed an impassable barrier "+
        "to the south have been thinned considerably, creating "+
        "a narrow opening.\n");

    add_exit("lf15", "northeast", 0);
    add_exit("lf14", "north", 0);
    add_exit("hf8",  "up", "@@basalt_stair");
    add_exit("lf19", "south", "@@tear_me");

    add_item(({"stair", "blocks", "stone", "staircase"}),
        "The blocks of basalt stone are brown-black and rectang"+
        "ular. They form a natural staircase rising up to the "+
        "top of the cliff.\n");
       
    add_cliff();
    add_moss();
    add_atrack();
    reset_domain_room(); 
}

int 
basalt_stair()
{
    write("\nYou carefully climb the basalt stairs.\n");
    return 0;
}

int 
tear_me()
{
    write("\nOuch! A thorn pricks you as you push south.\n");
    return 0;
}

  