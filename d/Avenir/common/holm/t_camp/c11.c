/*  file name:        /d/Avenir/common/holm/t_Camp/c11.c
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
    set_short("Dead end");
    set_long("You have come to a dead end. There is nothing of " + 
             "interest here, just a small grassy knoll surrounded "+
             "with bushes. It looks as though the undergrowth was "+
             "cleared away some time ago, but you fail to comprehend "+
             "how it was done, and to what purpose. "+
             "The only way out of here is back to the east.\n");

    add_exit("c5", "east", 0);
   
    add_ground();    
    add_bushes();
}


