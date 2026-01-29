/* file name:        /d/Avenir/rangorn/temp/c3.c
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
    set_short("Middle part of camp");
    set_long("The trail is wider here but thick underbrush makes it " +
             "impossible to go to the north or south. "+
             "The ground here is mostly bare bedrock that is sparely " +
             "covered with struggling vegetation. " +
             "The smoke that emanates from the east is getting " +
             "thicker now. You are probably very near " +
             "the source of the smoke.\n");

    add_exit("c2", "west", 0);
    add_exit("c6", "east", 0);
    
    add_ground(); 
}



