#include "../local.h"
inherit TDIR+"plain-3";

void
create_plains_room()
{
  add_exit(TDIR+"xak_link", "north", 0, 3);
  ::create_plains_room();
}
