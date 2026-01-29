#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"south"
    +".  The forest's edge continues "
    +"east to southwest"
    +", or you may re-enter the forest proper by heading "
    +"west"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/e7", "southwest", 0);
  add_exit(RHUN_DIR+"forest/e6", "west", 0);
  add_exit(RHUN_DIR+"forest/g6", "east", 0);
  add_stuff();
}
