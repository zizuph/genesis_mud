// file name:        /d/Avenir/common/holm/jungle/hf7.c
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
    set_short("large rent in the cliff wall");
    set_long("The living stone has separated from itself. You "+
        "stand at the base of a huge crack, between soaring "+
        "black walls that are sharp as glass in the jagged "+
        "places. Shadows dance on the walls, cast by the slow "+ 
        "writhing of the trees high above. Dead leaves and "+
        "other detritus makes your foothold uncertain.\n");

    add_crevice();
    add_ridge();

    add_exit("hf6", "east", 0);
    add_exit("hf4", "north", 0);

    add_item(({"shadow", "shadows"}),
        "The light of the Source high above barely reaches "+
        "the bottom of the crevice. Trees cast dancing shadows "+
        "upon the stone.\n");
    add_item(({"dead leaves", "detritus"}), "The ground is "+
        "littered with organic material, mostly pine needles.\n");

    reset_domain_room();
}

