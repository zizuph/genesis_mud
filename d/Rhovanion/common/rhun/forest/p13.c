#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"east"
    +".  The forest's edge continues "
    +"northwest to south"
    +", or you may re-enter the forest proper by heading"
    +" "
    +"west"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/p14","south",0);
  add_exit(RHUN_DIR+"forest/o13", "west", 0);
  add_exit(RHUN_DIR+"forest/o12","northwest",0);
  add_stuff();
}
