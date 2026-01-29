/*  part of the cave on Indy
 
    coder(s):	Deinonychus
 
    history:	DD.MM.YY	what done			who did
		28.02.93	created				Deinonychus
 
    purpose:	none
    exits:	none
 
    objects:	none
    npcs:	none
 
    quests:	none
    special:	none
 
    to do:	none
    bug:	none known
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
  set_short("Fireplace-room");
  set_long(BS("You are in the fireplace room. On the floor is a " +
    "very thick, luxurious, wooly carpet, inviting you to sit " +
    "down and watch the fire. The fireplace is made of marble " +
    "and looks used.\n"));
  add_exit(ROOM("living_room"), "north", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
