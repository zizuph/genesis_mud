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
	+"  To the south is a road."
     +"\n");

  add_exit(RHUN_DIR+"roads/section8/g","south",0);
  add_exit(RHUN_DIR+"forest/k5","east",0);
  add_exit(RHUN_DIR+"forest/i5","west",0);
  add_exit(RHUN_DIR+"forest/k4","northeast",0);
  add_stuff();
}
