#include "def.h"
inherit THIS_DIR+"edge_see";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge, near the Sea of Rhun");
  set_long("You stand at the western edge of a large"
    +" forest.  The Sea of Rhun is visible off to the west,  but is"
    +" unreachable from this point.  You may travel along the forest"
    +" edge to the "
    +"north or south"
    +", or re-enter the forest proper to the "
    +"east"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/k14","east",0);
  add_exit(RHUN_DIR+"forest/j15","south",0);
  add_exit(RHUN_DIR+"forest/j13", "north", 0);
  add_stuff();
}
