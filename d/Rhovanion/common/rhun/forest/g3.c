#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"north"
    +".  The forest's edge continues "
    +"east to west"
    +", or you may re-enter the forest proper by heading "
    +"either southeast or southwest"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/h4", "southeast", 0);
  add_exit(RHUN_DIR+"forest/f4", "southwest", 0);
  add_exit(RHUN_DIR+"forest/h3", "east", 0);
  add_exit(RHUN_DIR+"forest/f3","west",0);
  add_stuff();
}
