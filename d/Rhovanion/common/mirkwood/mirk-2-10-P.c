#include "/d/Rhovanion/defs.h"
inherit MIRK_DIR+"mirk-P";

void
create_map_room()
{
  ::create_map_room();
  remove_exit("west");
  add_exit(ANDUIN_DIR+"p5", "west", 0, 1);
}
