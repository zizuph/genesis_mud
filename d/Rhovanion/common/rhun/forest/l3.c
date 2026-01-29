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
    +"southeast"
    +", or you may re-enter the forest proper by heading"
	+" "
    +"south"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/m4","southeast",0);
  add_exit(RHUN_DIR+"forest/l4", "south", 0);
  add_stuff();
}
