#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("You stand at the western edge of the large"
    +" forest which lies to the north and east of the Sea of Rhun."
    +" Before you stand the vast and mostly-unexplored plains of Rhun,"
    +" stretching out as far as the eye can see. You can follow the"
    +" forest's edge here to the north or southeast.\n");

  add_exit(RHUN_DIR+"forest/a3","north");
  add_exit(RHUN_DIR+"forest/b5", "southeast");
  add_stuff();
}
