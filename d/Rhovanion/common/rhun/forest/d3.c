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
    +"to the east and southwest."
     +"\n");

  add_exit(RHUN_DIR+"forest/c4", "southwest", 0);
  add_exit(RHUN_DIR+"forest/e3", "east", 0);
  add_stuff();
}
