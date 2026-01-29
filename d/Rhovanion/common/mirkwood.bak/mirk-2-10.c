inherit "/d/Rhovanion/common/mirkwood/mirk_serv";
#include "/d/Rhovanion/defs.h"

void
create_map_room()
{
  remove_exit("west");
  add_exit(ANDUIN_DIR+"p5", "west", 0, 1);
}
