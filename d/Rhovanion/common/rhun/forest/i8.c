#include "def.h"
inherit THIS_DIR+"edge_see";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge, near the Sea of Rhun");
  set_long("You stand at the western edge of a large"
    +" forest.  The Sea of Rhun is visible off to the west,  but is"
    +" unreachable from this point.  You may re-enter the forest"
    +" proper to the "
	+"east, or follow its edge to the north"
    +"."
     +"\n");

  add_exit(RHUN_DIR+"forest/j8","east",0);
  add_exit(RHUN_DIR+"forest/i7","north",0);
  add_stuff();
}
