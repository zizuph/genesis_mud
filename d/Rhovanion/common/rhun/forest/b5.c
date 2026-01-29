#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"west"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  The trees grow more dense back to the "
    +"north"
    +", while it is also possible to follow this outer line of trees, "
    +"to the "
    +"northwest"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/a4","northwest",0);
  add_exit(RHUN_DIR+"forest/b4","north",0);
  add_stuff();
}
