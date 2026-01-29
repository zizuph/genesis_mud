/* file name:        /d/Avenir/rangorn/temp/c2.c
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

void
create_camp_room()
{
    set_short("Western part of camp, near entrance");
    set_long("You are standing at the entrance of some sort of camp. " +
             "The ground is barren and it looks almost as if it has " +
             "been polluted. You spot a wooden cage to the northeast, " +
             "and a tent against the cliff wall in the east. Smoke "+
             "rises in the east, and from the same direction an "+
             "awful stench emanates.\n");

    add_exit("c4", "east", 0);
    add_exit("c1", "west", 0);  
    add_exit("c5", "southeast", 0);
    add_exit("c3", "northeast", 0);   
 
    add_ground(); 
    add_item(({"cage", "wooden cage"}), "Not much to see from here. "+
        "You might get a better view if you go northeast.\n");
}



