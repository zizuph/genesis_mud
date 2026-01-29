// file name:        /d/Avenir/common/holm/shore/sh27.c
// creator(s):       Lilith, April 97
// revisions:        Sirra,  March 98
// purpose:
// note:		   place imprint.c here with the shorep.c
// bug(s):
// to-do:		   

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/shore/shore_base";

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


#include <ss_types.h>

string my_descrip();

/* Now create the room.  */
void
create_shore_room()
{
    set_short("Narrow strip of black sand framed by stone");
    set_long("The beach narrows here to a small strip of sand, "+
        "framed by a tumble of stone that prevents easterly "+
        "progress. The obsidian wall lies directly north, and "+
        "beyond it you can hear the cries of jungle creatures. "+
        "A western breeze carries the salt-tang scent of the sea, "+
        "and rustles the blades of the seagrass growing nearby. "+
        "\n");

    add_item(({"wall", "stone", "rock", "obsidian", "seawall"}),
        "Black volcanic glass from a long forgotten eruption, "+
        "this odd wall was probably formed by lava piling up as "+
        "it rapidly cooled in water. Presently, it acts as a "+
        "seawall, fortuitously protecting the inland jungle "+
        "from the dark waters of the Sybarus Sea. Imbedded in "+
        "the wall slightly above eye level is a carving of "+
        "some sort.\n");

    add_item("skeleton", "The fossilized skeleton @@my_descrip@@ "+
        ".\n");

    add_beachs();
    add_grass();
    add_rocks();
    add_exit("sh23", "west", 0);
    add_exit("sh25", "southwest", 0);
    reset_domain_room();
}

string
my_descrip()
{
    
    if (present("_Wolf_Quest_Imprints"))
    {
        if (this_player()->query_skill(SS_ANI_HANDL) >19)
            return "of a regal and majestic wolf";

	  else 
	      return "of an unidentifiable animal";
    }
    else
        return "of an unidentifiable animal";
    
}

	