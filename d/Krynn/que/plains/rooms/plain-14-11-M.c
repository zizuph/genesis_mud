#include "../local.h"
inherit TDIR+"plain-M";

void
create_plains_room()
{
  ::create_plains_room();
    add_exit(QUE_SHU_V_NORTH, "south");
}
