#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest. To the north "
    +"are the vastly-stretching plains that make up most of Rhun. "
    +"The trees grow more dense back to the south, "
    +"while it is also possible to follow this outer line of trees, "
    +"either to the east or west.\n");

  add_exit(RHUN_DIR+"forest/a3","west",0);
  add_exit(RHUN_DIR+"forest/b4", "south", 0);
  add_exit(RHUN_DIR+"forest/c3", "east", 0);
  add_stuff();
}
