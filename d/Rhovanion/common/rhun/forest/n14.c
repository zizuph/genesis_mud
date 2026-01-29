#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("You stand at the southern edge of the large"
    +" forest which lies to the north and east of the Sea of Rhun."
    +"  Before you stand the vast and mostly-unexplored plains of Rhun,"
    +" stretching out as far as the eye can see.  The interior of the"
    +" forest lies back to the north, or you might follow its"
    +" edge by heading east or southwest."
     +"\n");

  add_exit(RHUN_DIR+"forest/m15","southwest",0);
  add_exit(RHUN_DIR+"forest/n13","north",0);
  add_exit(RHUN_DIR+"forest/p14", "east", 0);
  add_stuff();
}
