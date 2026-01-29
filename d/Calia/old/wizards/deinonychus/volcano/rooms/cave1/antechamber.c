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
  set_short("Antechamber");
  set_long(BS("This is the antechamber to three halls. It looks " +
    "pretty empty. There would be enough place for another " +
    "nice object to expose. Maybe there'll be one some day.\n"));
  add_exit(ROOM("stegosaurus_hall"), "east", 0);
  add_exit(ROOM("brontosaurus_hall_2"), "southeast", 0);
  add_exit(ROOM("triceratops_hall"), "south", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
