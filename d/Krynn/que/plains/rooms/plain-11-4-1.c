#include "../local.h"
inherit TDIR+"plain-1";

void
create_plains_room()
{
  ::create_plains_room();
  add_exit(CAMP_V_EAST,  "northwest", 0, 1);
}
