#include "def.h"
inherit THIS_DIR+"inside";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("In the forest");
  set_long("Tall,  thick tree-trunks topped with a heavy"
    +" cover of green leaves lie all about you here.  It is quiet here"
    +" amongst the trees-- almost too quiet.  The usual birds and woodland"
    +" creatures are conspicuously absent.  The forest continues onward"
    +" all around you."
     +"\n");

  add_exit(RHUN_DIR+"forest/j6", "northwest", 0);
  add_exit(RHUN_DIR+"forest/l7","east",0);
  add_exit(RHUN_DIR+"forest/j8","southwest",0);
  add_exit(RHUN_DIR+"forest/k6","north",0);
  add_exit(RHUN_DIR+"forest/k8","south",0);
  add_stuff();
}
