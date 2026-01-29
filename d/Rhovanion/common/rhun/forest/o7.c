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
    +"north"
    +", or you may re-enter the forest proper by heading"
    +" west or southwest"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/n8","southwest",0);
  add_exit(RHUN_DIR+"forest/n7", "west", 0);
  add_exit(RHUN_DIR+"forest/o6","north",0);
  add_stuff();
}
