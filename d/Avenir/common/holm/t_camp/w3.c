/* file name:        /d/Avenir/common/holm/t_camp/w3.c
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
    set_short("man-made cave in the cliffwall");
    set_long("This place makes you feel uneasy.\n"+
        "Something isn't quite right here. Perhaps it is the "+
        "stench of dark magic which the mustiness barely camou"+
        "flages, or the eerie markings which cover the walls "+
        "as far as your eyes can see. Whatever it is, you have "+
        "an overwhelming urge to flee.\n");
    add_exit(T_CAMP +"w2", "west", 0, 1, 1);

    add_item(({"wall", "cliffwall", "markings", "runes"}), 
        "Magical runes have been meticulously painted upon the "+
        "walls with a dark, reddish paint...blood perhaps?\n");
    IN_IN;
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_S_DARK_LONG, "A very dark, musty room inside "+
       "the cliffwall.\n"); 
}





