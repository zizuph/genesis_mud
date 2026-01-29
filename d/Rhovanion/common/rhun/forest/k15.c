#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"south"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  The trees grow more dense back to the "
    +"north"
    +", while it is also possible to follow this outer line of trees, "
    +"either to the "
    +"east or west"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/j15","west",0);
  add_exit(RHUN_DIR+"forest/m15", "east", 0);
  add_exit(RHUN_DIR+"forest/k14","north",0);
  add_stuff();
}
