#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk down the street in this"
    +" large town.  A few people pass by; but it is mostly"
    +" empty.  You wonder if something frightened the people away"
    +"-- or killed them off.  To the northwest stands a small residence, "
    +"apparently still occupied, while the street splits to lead off"
    +" to the north, east, and southwest.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st3","east",0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st8", "southwest", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/house1", "northwest", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st1", "north", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"house","residence","building"}), "The"
    +" building is a small house, made entirely of wood.  It looks"
    +" as though some impoverished person still lives there.\n");
}
