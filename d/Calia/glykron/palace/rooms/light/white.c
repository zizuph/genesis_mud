/* White room in the Crystalline palace of the Calians.

   History:
            6/4/96     tidied up kroug handling         Maniac
           22/9/95    kroug raid code installed         Maniac
           8.12.94       Minor changes                  Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

object calian = 0;

void
reset_room()
{
    if (calian)
	return;

    calian = clone_object(MONSTER("white_calian"));
    calian->move(THIS);
    tell_room(THIS, QCTNAME(calian) + " arrives.\n");
}

void
create_room()
{
    set_short("The white room");
    set_long(break_string(
	"This is a large trapezoidal-shaped room whose east and west walls " +
	"slope away from you to the north.  " +
	"The room is filled with an extremely dazzling white light, and the " +
	"white walls are the most sparkling clean you have ever seen.  " +
	"The bed, dresser, and desk in this room are all made of white " +
	"birch.  " +
	"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_gold"), "south", 0);
    add_item("bed", "The white satin bed looks very comfortable.\n");
    add_item("dresser", "The white birch dresser is empty.\n");
    add_item("desk", "The white birch desk is neat and orderly.\n");
    reset_room();
}
