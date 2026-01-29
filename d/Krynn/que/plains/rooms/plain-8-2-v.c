#include "../local.h"
inherit TDIR+"plain-v";

void
create_plains_room()
{
  add_exit(CAMP_V_NORTH, "east",  0, 2, 1);
  add_exit(CAMP_V_WEST,  "south", 0, 2, 1);
  ::create_plains_room();
}
