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
  set_short("Crossing");
  set_long(BS("You're at a crossing. Southwards seems to be a sort " +
    "of exhibition. The northern rooms look more used and cosier.\n"));
  add_exit(ROOM("ancestor_hall_1"), "northeast", 0);
  add_exit(ROOM("bat_hall"), "southeast", 0);
  add_exit(ROOM("brontosaurus_hall_1"), "south", 0);
  add_exit(ROOM("visitors_cloak_room"), "northwest", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
