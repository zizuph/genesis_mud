#include "../local.h"
inherit TDIR+"plain-L";

void
create_plains_room()
{
  ::create_plains_room();
    add_exit(QUE_SHU_V_WEST, "east");
}
