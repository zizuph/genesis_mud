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
  set_short("Ancestor-hall");
  set_long(BS("You are in the Northern part of the ancester hall. " +
    "The walls are covered with paintings. Mostly portraits of " +
    "the owner's ancestors.\n"));
  add_item(({"painting","paintings"}), BS("The paintings all show " +
    "a certain family likeness.\n"));
  add_exit(ROOM("lounge"), "north", 0);
  add_exit(ROOM("ancestor_hall_1"), "south", 0);
  add_exit(ROOM("kitchen"), "northwest", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
