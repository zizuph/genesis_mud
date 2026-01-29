#include "../local.h"
inherit TDIR+"plain-1";

void
create_plains_room()
{
  add_exit(TDIR+"newports_link", "southwest", 0, 1);
  ::create_plains_room();
}
