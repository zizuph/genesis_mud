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
  set_short("Bat-hall");
  set_long(BS("Wow, this here looks like the cave of Batman. On the " +
    "ceiling are hanging hundreds of bats. Let's hope they don't feel " +
    "the need to fly out of the cave.\n"));
  add_item(({"bat", "bats"}), "These tiny black things look somehow " +
    "pretty.\n");
  add_exit(ROOM("trex_hall"), "north", 0);
  add_exit(ROOM("crossing"), "northwest", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
