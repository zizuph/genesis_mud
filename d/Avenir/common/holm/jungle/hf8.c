// file name:        /d/Avenir/common/holm/jungle/hf8.c
// creator(s):       Lilith, Dec 96
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/hf_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

int climb_down();

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
create_hf_room()
{
    set_short("Top of natural basaltic stairs");
    set_long("You stand at the top of a natural staircase formed "+
        "of basaltic stone. You cannot see its base, for a "+
        "thick canopy of leaves blocks your view. The dark "+
        "waters of the sea swirl at the shore's edge far "+
        "below. Greenish-yellow lichen grows like scabs on "+
        "the trees populating this ridge, and beyond them "+
        "the black prow of a rock juts up into the air.\n");

    add_lichen();
    add_ridge();

    add_exit("hf9", "east", 0);
    add_exit("lf18", "down", climb_down);
    
    add_item(({"stairs", "basaltic stairs", "staircase"}),
        "This staircase is naturally ocurring. It is made "+
        "of igneous rock which cooled and hardened into "+
        "strangely regular geometric shapes. It leads down "+
        "into the jungle.\n");

    reset_domain_room();
}

int
climb_down()
{
    write("\nThe way is steep, but you manage to safely reach the "+
        "bottom of the stone steps.\n\n");       
    return 0;
}