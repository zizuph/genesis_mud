/* file name:        /d/Avenir/common/holm/t_camp/t1.c
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
    set_short("Northeastern part of camp. Landslide");
    set_long("You manage to squeeze through the two big stones and " + 
        "find yourself in a landslide area. The ground is entirely "+
        "covered in shale from splintered rocks that have tumbled " + 
        "from the cliff high above. It looks like it might be "+
        "possible to continue going northwest.\n");

    add_exit("c7", "southwest", 0);
    add_exit("t2", "northwest", 0, 10, 1);

    add_item(({"shale", "landslide", "cliff", "splintered rocks", 
        "rock", "stone", "ground"}),
        "A great deal of stone has fallen from the cliff above, "+
        "creating a landslide of shale from the splintered stone.\n");
    add_item(({"northwest"}), "You think you might be able to "+
        "continue farther northwest.\n");
}


