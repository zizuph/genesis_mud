// file name:        /d/Avenir/common/holm/jungle/hf1.c
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
    set_short("Atop the cliff, near a cave entrance");
    set_long("You stand on a short stretch of level ground "+
        "at the top of the cliff. Below, in the west, "+
        "you can see light glinting on a pool of water. "+
        "The jungle is a glowing jewel-green carpet at "+
        "your feet. There is a gaping black maw in the "+ 
        "humped and spiny stone of the cliff face, and a "+
        "well-worn path leading to it.\n");

    add_moss();
    add_exit("hf2", "east", 0);
//    add_exit(CAVE + "c1", "south", 0);

    add_item(({"pool", "water", "west", "below"}), 
        "The pool of water resembles a small puddle"+
        " from this height. Its center whirls ominously.\n");
    add_item(({"path", "well-worn path"}),
        "This path continues south toward the face of cliff "+
        "and curves east toward the crevice.\n");
    add_item(({"maw", "gaping maw", "mouth", "cliff face"}),
        "It is irregularly-shaped. Though natural, this "+
        "opening in the living stone of the cliff-face "+
        "shows evidence of having been enlarged.\n");
    add_item(({"evidence", "grooves"}), 
       "The stone is marked by the kind of grooves made by "+
       "chiseling.\n");

    reset_domain_room();
}
