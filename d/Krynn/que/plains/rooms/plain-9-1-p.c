#include "../local.h"
inherit TDIR+"plain-p";

void
create_plains_room()
{
  add_exit(CAMP_V_NORTH, "south", 0, 2, 1);
  ::create_plains_room();
}
