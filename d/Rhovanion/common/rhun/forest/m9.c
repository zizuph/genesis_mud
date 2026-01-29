#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("You stand at the eastern edge of the large"
    +" forest which lies to the north and east of the Sea of Rhun."
    +"  Before you stand the vast and mostly-unexplored plains of Rhun,"
    +" stretching out as far as the eye can see.  The interior of the"
    +" forest lies back to the west and northwest."
     +"\n");

  add_exit(RHUN_DIR+"forest/l8","northwest",0);
  add_exit(RHUN_DIR+"forest/l9", "west", 0);
  add_stuff();
}
