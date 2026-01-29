/* file name:        /d/Avenir/common/holm/t_camp/c5.c
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
    set_short("southwest in troloby camp");
    set_long("The bushes around here are very thick but someone or " +
             "something has managed to clear a path to the west. " +
             "You notice that smoke is rising from the east.\n");

    add_exit("c2", "northwest", 0);
    add_exit("c11", "west", 0);  

    add_ground();  
    add_bushes();
    
    add_cmd_item("tent", "listen", "As you put your ear near the surface " + 
                "of the tent you can barely hear someone mumbling: " +
                "'..yhose blabjabberi...dough..h.w c'.'\nThen suddenly " +
                "there is silence from inside the tent. Perhaps you " +
                "made some noise that caused the person to think someone " +
                "was eavesdropping on him.\n");

    add_item(({"tent"}),
               "A brown tent made of leather. It has been sealed shut "+
               "from the inside. You think that you can hear someone "+
               "moaning inside the tent.\n");
    
    add_item(({"cage"}),
               "A cage that contains something that resembles a pair " +
               "of human hands.\n");    
}



