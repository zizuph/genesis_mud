/* file name:        /d/Avenir/common/holm/t_camp/t2.c
 *  creator(s):      (Rangorn , Feb 97)
 *  revisions:
 *  purpose:
 *  note:
 *  bug(s):
 *  to-do:  
 */

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/t_camp/camp_base";

/* Include the local area defines, etc */
#include "../holm.h"

/* Now create the room.  */
void create_camp_room()
{
    set_short("Sheltered cliffside northeast of camp");
    set_long("You have reached a dead end. Rocks have tumbled from "+
        "the unstable cliffside, forming a space sheltered from "+
        "casual view. Scanning the rubble, you notice that you will "+
        "not be able to go back the way you came. There is, however, "+
        "a roundabout way to the southwest. The ground is "+
        "swept and free of debris save for a pile of fresh straw "+
        "secreted beneath a low, horizontal slab.\n");

    add_exit("t1", "southwest", 0, 10, 1);

    add_item(({"straw", "pile", "fresh straw", "pile of straw",
        "pallet", "primitive pallet"}),
        "Freshly cut, it smells sweet and earthy. It forms a "+
        "primitive pallet beneath the rock slab.\n");
    add_item(({"slab", "rock slab", "low slab", "horizontal slab"}),
        "A natural formation of the cliff wall, this slab of rock "+
        "runs parallel to the ground at about shoulder height, "+
        "making it a decent place to shelter.\n");    
    add_item(({"rocks", "ground"}), "The ground here is littered "+
        "with large rocks, but it shows signs of having been swept "+
        "with a primitive broom and all shale removed.\n");
    add_item(({"rubble", "southeast", "path"}),
        "The path you originally took over the rubble is impossible "+
        "to follow from here, but you notice a possible way back to "+
        "the southwest.\n");
}


