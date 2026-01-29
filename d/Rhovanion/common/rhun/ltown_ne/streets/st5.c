#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street heads from north to south here."
    +"  It is not paved, but its dirt surface is easily defined, and"
    +" well-marked.  A meeting hall lies just to the west, and"
    +" there is a simple house to the southeast.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st6", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st3", "north", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/house2", "southeast", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/boardroom", "west", 0);


  add_item(({"house","residence","building"}), "The"
    +" building is a small house, made entirely of wood.  It looks"
    +" as though some impoverished person still lives there.\n");
  add_item(({"hall", "meeting hall", "Meeting Hall"}), "The"
    +" meeting hall is just to the west.  It, like the other buildings"
    +" around here, is made wholly from wood.  There seems to be little"
    +" traffic in and out of it these days, though it is still open"
    +" to visitors.\n");
}
