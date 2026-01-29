/* file name:        /d/Avenir/common/holm/t_camp/c9.c
 *  creator(s):     (Rangorn , Feb 97)
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
    set_short("Eastern part of camp, used as a refuse dump");
    set_long("You have reached a largish clearing surrounded "+
             "by thriving thorn bushes. The hard-packed soil "+
             "is covered with refuse dumped here by the area "+
             "inhabitants. The stench is so revolting that "+
             "you have to choke back an overwhelming urge to "+
             "vomit. The only way out is to follow the trail "+
             "leading west.\n"); 

    add_exit("c8", "west", 0);

    add_ground();  
    add_bushes();

    add_item(({"west", "west trail", "west path", "path", "trail"}),
               "You bend down and examine the trail and you notice " + 
               "that it isn't used very often.\n");

    add_item(({"garbage", "refuse", "trash", "heap"}),
               "All kinds of garbage has been dumped here. As you bend " +
               "down to examine the garbage heap more closely you notice " +
               "that a corpse has been dumped here recently and " +
               "it is just about half rotten.\n");
    add_item(({"corpse", "rotten corpse", "half rotten corpse"}),
               "No wonder why it stinks so bad in here! There "+
               "is a half-rotted corpse in this garbage heap.\n");
     
}
