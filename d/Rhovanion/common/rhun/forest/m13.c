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
     +" branches overhead.  To the south lies a large clearing."
     +"\n");

  add_exit(RHUN_DIR+"forest/k14","southwest",0);
  add_exit(RHUN_DIR+"tower/clearing/cl7","south",0);
  add_stuff();
}
