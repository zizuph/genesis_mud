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
  set_short("Lounge");
  set_long(BS("You entered the lounge. It looks rather unused. " +
    "There is a wooden bed, a bedpost and on top of it you " +
    "discover a candlestick.\n"));
  add_item(({"bed", "wooden bed"}), BS("The wooden bed looks neat, " +
    "but as everything in this room - unused.\n"));
  add_item(({"candlestick"}), BS("The candlestick is made of brass " +
    "and devoid of candles.\n"));
  add_exit(ROOM("ancestor_hall_2"), "south", 0);
  add_prop(ROOM_I_LIGHT, 0);
}
