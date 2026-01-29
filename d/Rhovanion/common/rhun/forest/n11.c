#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"east"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  The trees grow more dense back to the "
    +"west and south"
    +", while it is also possible to follow this outer line of trees, "
    +"either to the "
    +"northwest or southeast"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/m10","northwest",0);
  add_exit(RHUN_DIR+"forest/o12", "southeast", 0);
  add_exit(RHUN_DIR+"forest/n12","south",0);
  add_exit(RHUN_DIR+"forest/m11","west",0);
  add_stuff();
}
