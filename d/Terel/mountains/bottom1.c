/* room2.c
   Mort 911004 */
/*
 * Lucius, Jan 2018: ROOM_M_NO_TELEPORT_TO added.
 */

inherit "/std/room";
#include <stdproperties.h>

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */
void
create_room()
{
    set_short("Cavern");
    set_long("This cavern reeks of death, bones are strewn about the " +
      "ground. A large puddle lies here, dark and fetid. There " +
      "is ash all about.\n");

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    add_exit("hole", "up",0);
    add_exit("bottom2", "south", 0);
}
