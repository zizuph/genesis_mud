// file name:        /d/Avenir/common/holm/jungle/hf5.c
// creator(s):       Lilith, Dec 96
// revisions:	   Sirra added the wolf bone bit. March 1998.	
// purpose:	   find a wolf bone (RIB_ID) by searching log.
// note:           add the climb down to lf11
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/hf_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include "/d/Avenir/common/holm/wolf.h"

int found;

string find_wolf_bone(object player, string str);

void
reset_domain_room()
{
    found = 1;
    set_searched(0);
}

/* Now create the room.  */
void
create_hf_room()
{
    set_short("Overlooking an avalanche");
    set_long("You stand at the top of a series of natural stone "+
        "pillars. Broken trees and logs litter the ground. " +
	  "A mist-shrouded lowland forest crowds the "+
        "base of the pillars, undeterred in its growth by the "+
        "avalanche scar disfiguring the slope below. South, a "+
        "path winds toward the tortured figures of stunted "+
        "pine trees.\n");

    add_prop(OBJ_S_SEARCH_FUN, "find_wolf_bone");
    add_prop(OBJ_I_SEARCH_TIME, 2);

    add_avalanche();
    add_crevice();
    add_ridge();
    add_exit("hf6", "south", 0);

    add_item(({"log", "logs", "trees", "tree"}),
	"The logs are the long and spindly remains of toppled trees "
	+ "swept over by an avalanche.\n"); 
    add_item("path", "It follows the ridge.\n");
    reset_domain_room();
}

string
find_wolf_bone(object player, string str)
{
    object bone;

    if (found<1)
	return "";

    if (str != "logs"&& str != "log" && str != "tree" && str != "trees")
	return "";

    found--;
	
    bone = clone_object(WOLF_BONE + "rib.c");
    bone->move(this_player(),1);

    return "You find a rib bone in the log!\n";
}


