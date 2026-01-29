// file name:        /d/Avenir/common/holm/jungle/hf4.c
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

int climb_up();

/* Now create the room.  */
void
create_hf_room()
{
    set_short("Bottom of a crevice");
    set_long("You stand within a huge crack in the dark stone of "+
        "the cliff. Handholds and footholds have been cut "+
        "into stone that is sharp as glass in the jagged "+
        "places. Shadows dance on the walls, cast by the "+
        "slow writhing of the trees overhead.\n");


    add_crevice();

    add_exit("hf7", "south", 0);
    add_exit("hf3", "up", climb_up);

    add_item(({"handhold", "handholds", "foothold", "footholds", 
        "hollow", "hollows"}),
        "Hollows have been chiselled into the stone to make "+
        "it possible for people to climb up and down the side "+
        "of the crevice.\n");
    add_item(({"shadow", "shadows"}),
        "The light of the Source high above barely reaches "+
        "the bottom of the crevice. Trees cast dancing shadows "+
        "upon the stone.\n");
    reset_domain_room();
}

int
climb_up()
{
    write("\nYou use the hollows etched into the side of the "+
        "crevice to climb upward.\n\n");
    return 0;
}     