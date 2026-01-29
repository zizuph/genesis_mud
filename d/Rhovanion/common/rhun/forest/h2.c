#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"north and west"
    +".  The forest's edge continues "
    +"to the north and south."
     +"\n");

  add_exit(RHUN_DIR+"forest/h1.c", "north", 0);
  add_exit(RHUN_DIR+"forest/h3.c", "south", 0);
  add_stuff();
}
