#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The building is completely empty. There is no " +
    "furniture. Even the walls that once divided the " +
    "floor into several rooms have been pulled down so that only " +
    "some rubble is left of them. A dark hole in the ceiling tells you that there " +
    "must be a floor above, but there is no way to get there. A flight " +
    "of stone steps is leading down into the cellar.");
  add_item(({"flight","steps","stone steps","stairs"}), BS(
    "A flight of steps hewn from dark rock is leading down into " +
    "the cellar of the building. From below, a terrible stench " +
    "is rising to your nose. You can see only darkness and shadows " +
    "down there. \n"));
  add_item(({"hole","ceiling"}), BS(
    "The hole in the ceiling tells you that there is another floor " +
    "above this one. Probably, once there were some wooden stairs or " +
    "a ladder leading up, but they have long ago been vandalized and " +
    "no remains of them can be seen. \n"));
  add_item(({"floor","ground","rubble"}), BSN(
    "The stone floor is covered by the remains of the walls that once divided " +
    "this floor into several rooms."));
  set_road(5);
  set_side("west");

  add_exit(MORGUL_DIR + "city/mmr1","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/cellar1","down","@@check_exit",1);
}
