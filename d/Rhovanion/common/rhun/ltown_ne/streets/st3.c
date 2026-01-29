#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street, outside the post office");
  set_long("The street makes a crossroads here, with"
    +" branches heading off to the east, west, and south."
    +"  To the north lies the town post office, a rather small"
    +" wooden building.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st4","east",0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st2", "west", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st5", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/po", "north", 0);

  add_item(({"post office", "office", "building"}), "The"
    +" town post office is made entirely of wood, like much of this"
    +" town.  It seems rather small for its important function."
    +"  Though much of this place is deserted, the post office is"
    +" still fully operational.  The door is open; you are welcome to"
    +" step inside by heading north.\n");
  add_item(({"street", "streets"}), "The street forks"
    +" here.  Branches lead to the east, west, and south.\n");
}
