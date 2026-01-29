#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast "
    +"plains of Rhun lying to the north. The forest's edge continues "
    +"to the east and south.\n");

  add_exit(RHUN_DIR+"forest/a4", "south");
  add_exit(RHUN_DIR+"forest/b3", "east");
  add_stuff();
}
