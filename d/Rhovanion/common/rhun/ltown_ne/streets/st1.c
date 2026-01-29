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
    +" well-marked.  The town gate lies to the north.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st2", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/northgate", "north", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"house","residence","building"}), "The"
    +" building is a small house, made entirely of wood.  It looks"
    +" as though some impoverished person still lives there.\n");
}
