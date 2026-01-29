#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("You stand at the northern edge of the large"
    +" forest which lies to the north and east of the Sea of Rhun."
    +"  Before you stand the vast and mostly-unexplored plains of Rhun,"
    +" stretching out as far as the eye can see.  You might follow the"
    +" forest's edge by heading east or south from here."
     +"\n");

  add_exit(RHUN_DIR+"forest/i1","east",0);
  add_exit(RHUN_DIR+"forest/h2","south",0);
  add_stuff();
}
