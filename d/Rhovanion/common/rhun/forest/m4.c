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
    +"southeast and west"
    +", while it is also possible to follow this outer line of trees, "
    +"either to the "
    +"east or northwest"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/l4","west",0);
  add_exit(RHUN_DIR+"forest/l3", "northwest", 0);
  add_exit(RHUN_DIR+"forest/n4","east",0);
  add_exit(RHUN_DIR+"forest/n5","southeast",0);
  add_stuff();
}
