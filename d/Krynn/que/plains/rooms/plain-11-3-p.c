#include "../local.h"
inherit TDIR+"plain-p";

void
create_plains_room()
{
  ::create_plains_room();
  add_exit(CAMP_V_EAST,  "west", 0, 2, 1);
}
