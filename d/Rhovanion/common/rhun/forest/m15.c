#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"south and east"
    +".  The forest's edge continues "
    +"northeast to west from here."
    +"  Additionally, a large clearing lies just to the north."
     +"\n");

  add_exit(RHUN_DIR+"forest/n14", "northeast", 0);
  add_exit(RHUN_DIR+"forest/k15", "west", 0);
  add_exit(RHUN_DIR+"tower/clearing/cl1", "north", 0);
  add_stuff();
}
