#include "/d/Gondor/defs.h"
inherit "/d/Gondor/common/mirkwood/forest/mirk-P";

void
create_map_room()
{
  ::create_map_room();
  remove_exit("west");
}
