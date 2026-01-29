#include "def.h"
inherit THIS_DIR+"inside";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("In the forest");
  set_long("This dense forest lies just northeast of the Sea of"
     +" Rhun.  It is oddly silent, as though the natural birds and other"
     +" creatures have been frightened off.  On the ground is a thick blanket"
     +" of fallen leaves, heavily shadowed by the dense canopy of leaves and"
     +" branches overhead."
     +"\n");

  add_exit(RHUN_DIR+"forest/c8", "south", 0);
  add_exit(RHUN_DIR+"forest/b7","west",0);
  add_stuff();
}
