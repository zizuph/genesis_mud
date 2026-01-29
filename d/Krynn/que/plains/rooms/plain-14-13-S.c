#include "../local.h"
inherit TDIR+"plain-S";

void
create_plains_room()
{
    add_exit(QUE_SHU_V_SOUTH, "north");
  ::create_plains_room();
}
