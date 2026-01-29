#include "../local.h"
inherit TDIR+"plain-h";

void
create_plains_room()
{
  add_exit(TDIR+"xak_link", "east", 0, 1, 4);
  ::create_plains_room();
}
