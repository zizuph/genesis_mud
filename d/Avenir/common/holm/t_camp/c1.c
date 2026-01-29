/* file name:	c1.c
 * creator(s):	(Rangorn , Feb 97)
 * revisions:
 * purpose:
 * note:
 * bug(s):
 * to-do:
 */

# pragma strict_types
# include "../holm.h"

inherit "/d/Avenir/common/holm/t_camp/camp_base";

/* Now create the room.  */
void
create_camp_room()
{
    set_short("Entrance to the camp.");
    set_long("The jungle is less dense here and the beginnings of a "+
             "trail meanders through bushes to the east. As you " +
             "peer through the undergrowth, you can make out some " +
             "something that resembles a cage northeast of here. "+
             "The stench of rotting flesh and mysterious brews "+
             "emanates from the east.\n");

    add_exit("c2", "east", 0);
    add_exit(JUNG +"lf22", "west", 0);
  /*  add_ground();  */
    add_bushes();

    add_item(({"east", "east trail", "east path", "path", "trail"}),
               "You bend down and examine the trail and you notice " + 
               "that it isn't used very often.\n");
}
