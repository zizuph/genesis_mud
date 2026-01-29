/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_std_herbs("underground");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    set_short("a large cave");
    set_long("This is the inside of a large cave. It's pitch black and " +
        "stuffy. A ledge runs from the west and ends here. The walls " +
        "are rough looking and the ceiling lost in the darkness.\n");

    add_item(({"ledge"}),
        "It is an irregular shaped of rock. The ledge is rough and wide " +
        "and connects from the west.\n");

    reset_room();

    add_exit(TUN_DIR + "cv04", "east");
    add_exit(TUN_DIR + "cv02", "west");
}

/*
check_drowwep()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->id("drowwep"))
      {
      write("Your drow weapon disintegrates!\n");
      ob[i]->remove_object();
      return 0;
   }
   return 0;
}
*/

void
reset_room()
{
    set_searched(0);
}