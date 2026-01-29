/*  part of the cave on Indy
 
    coder(s):   Deinonychus
 
    history:    DD.MM.YY        what done                       who did
		28.02.93        created                         Deinonychus
 
    purpose:    none
    exits:      none
 
    objects:    none
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/
 
 
inherit "/std/room";
#include "cave1.h"
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
  set_short("Sleeping-room");
  set_long(BS("You're in the sleeping room (snore, snore). Do not " +
    "dare to wake it up. Sleeping rooms are know to lose it if " +
    "disturbed (you may laugh now).\n") + 
    BS("Right, there's also a bed in the sleeping room (where else " + 
    "should the room sleep?). Above the bed's a sign.\n"));
  add_item("sign", "Reading it might help.\n");
  add_cmd_item("read", "sign", "Snore, snore!\n");
  add_item("bed", "The bed is large, comfortable and inviting. " +
    "You would certainely use it if the room didn't occupy it.\n");
  add_exit(ROOM("armour_room"), "north", 0);
  add_prop(ROOM_I_LIGHT, 0);
  add_prop(ROOM_I_INSIDE, 1);
}
