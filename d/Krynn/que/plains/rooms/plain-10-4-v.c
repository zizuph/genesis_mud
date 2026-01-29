#include "../local.h"
inherit TDIR+"plain-v";

void
create_plains_room()
{
  ::create_plains_room();
  add_exit(CAMP_V_EAST,  "north", 0, 2, 1);
  add_exit(CAMP_V_SOUTH, "west",  0, 2, 1);
}
