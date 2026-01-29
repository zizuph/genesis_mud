#include "def.h"
inherit THIS_DIR+"edge_see";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge, near the Sea of Rhun");
  set_long("This is the western side of a dense forest."
    +"  You have emerged from the trees to view the Sea of Rhun"
    +" off to the west,  though you cannot reach it from here.  The way"
    +" along the forest's edge continues from "
    +"north to east"
    +".  You can also plunge back into the trees by heading"
    +" northeast"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/k15","east",0);
  add_exit(RHUN_DIR+"forest/k14", "northeast", 0);
  add_exit(RHUN_DIR+"forest/j14", "north", 0);
  add_stuff();
}
