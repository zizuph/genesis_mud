#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"south and east"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  The trees grow more dense back to the "
    +"west"
    +", while it is also possible to follow this outer line of trees, "
    +"to the "
    +"northeast"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/d7","west",0);
  add_exit(RHUN_DIR+"forest/f6", "northeast", 0);
  add_stuff();
}
