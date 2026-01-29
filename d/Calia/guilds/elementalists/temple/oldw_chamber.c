
 /* West Chamber of the Worshipper Temple
  * by Jaacar
  * July 22nd, 1996
  * Based on library code originally coded by Elessar, April 1992
  * Modifications by Maniac, 10/10/96
  */


#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <composite.h>
#include "defs.h"

void
create_room()
{
    set_short("A small chamber");
    set_long("This chamber is fairly small, the walls probably "+
        "as long as two humans lying head to toe. The walls are "+
        "made of stones, wood, and mud. On the western wall you "+
        "notice small slots carved into the stone, which appear "+
        "to be shelves of some sort. These slots now lie empty "+
        "and abandoned. Against the southern wall you see a small "+
        "desk. You can head out back into the entranceway to the "+
        "east.\n");
        
    add_item(({"slot","slots"}),"These slots probably contained "+
    	"scrolls at one time but now are empty.\n");
    add_item("desk","It is a small wooden desk, most likely "+
        "used by the inhabitants of this temple for writing "+
        "scrolls for this place.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(ELEMENTALIST_TEMPLE+"old_entrance","east",0,1);
}
