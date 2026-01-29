#include "../local.h"
inherit TDIR+"plain-1";

void
create_plains_room()
{
  add_exit(CAMP_V_SOUTH, "north",  0, 1);
  ::create_plains_room();
}
