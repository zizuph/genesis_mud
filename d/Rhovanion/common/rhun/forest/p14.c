#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"east"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  It is also possible to follow this outer line of trees, "
    +"either to the "
    +"west or north"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/n14","west",0);
  add_exit(RHUN_DIR+"forest/p13","north",0);
  add_stuff();
}
