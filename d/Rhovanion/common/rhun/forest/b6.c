#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("The heavy forest ends here, leaving the vast"
    +" plains of Rhun lying to the "
    +"west and north"
    +".  The forest's edge continues "
    +"to the southwest"
    +", or you may re-enter the forest proper by heading "
    +"either east or south"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/b7", "south", 0);
  add_exit(RHUN_DIR+"forest/a7", "southwest", 0);
  add_exit(RHUN_DIR+"forest/c6", "east", 0);
  add_stuff();
}
