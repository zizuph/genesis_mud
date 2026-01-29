#include "../local.h"
inherit TDIR+"plain-A";

void
create_plains_room()
{
    add_exit(QUE_SHU_V_EAST, "west");
  ::create_plains_room();
}
