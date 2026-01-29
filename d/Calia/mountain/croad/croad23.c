/* Maniac 27/3/95 */ 
/* Slip code by Overlord */ 
/* Modified, Maniac 19/9/95 

   History: 

   2/7/01   arm_me call removed (now called from std kroug)   Maniac 
*/ 

inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

object kroug;

void
reset_room()
{
    if (!objectp(kroug)) {
        kroug = clone_object(MOUNTAIN_MONSTERS+"kroug_scout");
        kroug->move_living("M", this_object());
        kroug->command("hide");
        tell_room(this_object(), QCTNAME(kroug) + " creeps stealthily in.\n");
   }
}


void
create_room()
{
    make_the_room("The road leads upwards to the west " +
      "and down to the northeast.\n", 24);
    add_exit(CROAD+"croad24","west","@@slip", 2);
    add_exit(CROAD+"croad22","northeast", "@@slip");
    add_item(({"plateau"}), "You can now see the edge of the plateau " +
          "at the top of the mountain, some fifty yards above you.\n");

    reset_room();
}


