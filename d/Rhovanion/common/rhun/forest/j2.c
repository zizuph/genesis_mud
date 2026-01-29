#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"north and east"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  The trees grow more dense back to the "
    +"west and south"
    +", while it is also possible to follow this outer line of trees, "
    +"either to the "
    +"northwest or southeast"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/i2","west",0);
  add_exit(RHUN_DIR+"forest/j3","south",0);
  add_exit(RHUN_DIR+"forest/k3", "southeast", 0);
  add_exit(RHUN_DIR+"forest/i1", "northwest", 0);
  add_stuff();
}
