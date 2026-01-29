/* 
   Silver room in the Crystalline palace of the Calians
 
   Coded by Glykron.

   History: 
         6/4/96     tidied up kroug handling            Maniac
         12/12/95     vandalism possibility added       Maniac
         22/9/95     Kroug raid code installed               Maniac
          8.12.94         Minor changes                      Maniac
*/


#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "/d/Calia/std/vandalism.c"

object calian = 0;

void
reset_room()
{
    if (calian) return;
    calian = clone_object(MONSTER("silver_calian"));
    calian->move(THIS);
    tell_room(THIS, QCTNAME(calian) + " arrives.\n");
}

void
create_room()
{
    set_short("The silver room");
    set_long(
	"This is a trapezoidal room whose east and south walls slant away " +
	"from you to the northwest.  " +
	"The walls of the room are painted silver.  A small silver clock " +
	"hangs on the east wall, and underneath it is a bed with silver " +
        "sheets.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_gold"), "east", 0);
    add_exit(ROOM("light_training"), "south", 0);
    add_exit(ROOM("light_good"), "northwest", 0);

    add_item(({"wall", "walls"}), "The walls of this room are painted " +
               "silver.\n");

    add_item(({"clock", "small clock", "small silver clock", "silver clock"}), 
              "A small silver clock is hung on the " +
              "east wall above the bed. It seems to be in perfect " +
              "condition.\n");
    add_item_possible_vandalism("small silver clock", 
              "A small silver clock is hung on the " +
              "east wall above the bed.", ({"shatter", "break" }), 
              35);

    add_item("bed", "A bed with a silver frame and silver colored sheets. " +
                    "It seems to be in perfect condition.\n");
    add_item_possible_vandalism("bed", "A bed with a silver frame and " +
                       "silver colored sheets.", ({"break", "smear"}), 40);  
    reset_room();
}

void
init()
{
    ::init();
    init_vandalism();
}

