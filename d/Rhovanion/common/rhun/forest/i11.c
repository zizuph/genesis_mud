#include "def.h"
inherit THIS_DIR+"edge_see";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge, near the Sea of Rhun");
  set_long("This is the western side of a dense forest."
    +"  You have emerged from the trees to view the Sea of Rhun"
    +" off to the west,  though you cannot reach it from here.  The way"
    +" back into the forest lies to the east."
     +"\n");

  add_exit(RHUN_DIR+"forest/j11","east",0);
  add_stuff();
}
