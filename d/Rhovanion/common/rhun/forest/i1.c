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
    +"west to southeast"
    +", or you may re-enter the forest proper by heading"
    +" south"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/h1","west",0);
  add_exit(RHUN_DIR+"forest/j2","southeast",0);
  add_exit(RHUN_DIR+"forest/i2", "south", 0);
  add_stuff();
}
