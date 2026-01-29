/*
 *   This is the Town hall, coded by Vader on 6/27/92
 *  Updated by Shinto 10-19-98
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
object door;

void 
create_room() 
{
     object board;
     set_short("Calathin Town Hall");
     set_long("This is the Town Hall of Calathin, "
      + "where local residents come to voice their opinion (as "
      + "if it was going to make a difference!).  The entire "        
      + "building is constructed from wood, and the smell of the "  
      + "pine is astounding.  Even the floor is shiny and looks "
      + "clean enough to eat from.  Due to pressing problems, "
    + "the rest of the building is off limits to visitors.\n");

    board=clone_object(CALATHIN_DIR + "board.c");
    board->move(this_object());
    door = clone_object(CALATHIN_DIR + "obj/hall_door");
    door->move(TO);

    add_item(({"floor", "wood floor", "pine floor"}), 
        "It shines, due to its polished finish.  Best wood around.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
}
