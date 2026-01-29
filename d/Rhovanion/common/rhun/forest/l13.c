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
    +" to the north, and a small, abandoned town lies to the west."
     +"\n");

  add_exit(RHUN_DIR+"forest/l12", "north", 0);
  add_exit(RHUN_DIR+"stown5/eastside", "west", 0);
  add_stuff();
}
