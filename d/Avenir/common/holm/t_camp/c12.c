/* file name:        /d/Avenir/common/holm/t_camp/c12.c
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
    set_short("Northwestern part of camp.");
    set_long("You have reached a dead end and the only way out of "+
             "here is to retrace your steps to the south. Someone "+
             "has strewn hay here and there are also a couple " +
             "of mugs laying around on the ground. " +
             "The ever-present thorn bushes surround you in all " +
             "directions except to the south.\n");

    add_exit("c3", "south", 0);
    
    add_ground(); 
    add_bushes();
     
    add_item(({"mug","cup","mugs","cups"}),
        "Mugs made of steel and of various sizes lay scattered on " + 
        "the ground.\n"); 
     
    add_item(({"hay"}),
        "Someone has put hay on the ground, obviously to be used as " +
        "a simple bed.\n");
    
}

int
do_mug(string str)
{
  
    if (str=="mug" || str=="cup") 
    {
        write("You pick up one of the mugs but it is so unbelievably " +
            "dirty and filthy that you decide drop it.\n"); 
        say(QCTNAME(TP) +" picks up a mugs but "+ TP->query_pronoun() + 
            " is obviously so disgusted by it that "+ TP->query_pronoun() + 
            " decides to drop it.\n"); 
        return 1;
    }
    else
        return 0;
}


void
init()
{
    add_action(do_mug,"get");
    ::init();
}

