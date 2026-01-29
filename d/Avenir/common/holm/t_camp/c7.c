/* file name:        /d/Avenir/common/holm/t_camp/c7.c
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
    set_short("Northeastern part of camp.");
    set_long("Big stones have been scattered around here. Large, "+
             "irregular gashes form pits in the bare bedrock. "+
             "Something unnatural has been at work here, as though "+
             "an unworldly power was wielded to cut and lift these "+
             "stones from the living rock upon which you stand. "+
             "Vegetation is very rare, and what little remains is "+
             "so damaged it may not survive. To the south you can "+
             "see ominous white smoke rising. You notice a small " +
             "path that is leading northeast between two big stones.\n");

    add_exit("c6", "south", 0);
    add_exit("t1", "northeast", 0);
    add_exit("c3", "west", 0);    

    add_ground(); 

    add_item(({"rock", "rocks", "stones", "stone"}),
              "Big rocks that have been cut out from the bedrock. " +
              "You notice that there is black soot on some of the " +
              "stones.\n"); 
    add_item(({"pit", "gashes", "irregular gashes", "pits"}),
              "Shallow and deep, narrow and wide, these many pits "+
              "appear to have been left behind when the stones "+
              "that litter the ground were torn away.\n");
}


