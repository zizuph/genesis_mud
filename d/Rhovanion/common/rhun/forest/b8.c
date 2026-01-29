#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"west"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  It is also possible to follow this outer line of trees, "
    +"either to the "
    +"northwest or east"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/a7","northwest",0);
  add_exit(RHUN_DIR+"forest/c8","east",0);
  add_stuff();
}
