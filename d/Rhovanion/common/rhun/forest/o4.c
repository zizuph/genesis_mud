#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"north and east"
    +".  The forest's edge continues "
    +"south from here."
     +"\n");

  add_exit(RHUN_DIR+"forest/o5", "south", 0);
  add_stuff();
}
