#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("By the dock");
  set_long("The street curves here, leading back into"
    +" town to the northeast.  South of here is a boat house,  while"
    +" a long wooden pier extends into the Sea of Rhun near the mouth"
    +" of the River Carnen.\n");

  add_exit(RHUN_DIR+"ltown_ne/bldgs/boat_house", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st2", "northeast", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/dock", "west", 0);

  add_item("street", "The street leads back to the northeast.\n");
  add_item(({"pier", "dock"}), "The pier is just to the"
    +" west, standing out in the water of a bay on the northwest corner"
    +" of the Sea of Rhun, near where the River Carnen empties into it.\n");
  add_item(({"house", "building", "boat house"}), "The"
    +" boat house lies just south of here.  It, like the other"
    +" buildings around here, is made entirely of wood.\n");
}
