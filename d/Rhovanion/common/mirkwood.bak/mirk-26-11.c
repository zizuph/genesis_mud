inherit "/d/Rhovanion/common/mirkwood/mirk_serv";
#include "/d/Rhovanion/defs.h"

void
create_map_room()
{
  remove_exit("east");
  add_exit(ESG_DIR+"westbridge2", "east", 0, 1);
}
