#include "def.h"
inherit THIS_DIR+"inside";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("In the forest");
  set_long("Tall,  thick tree-trunks topped with a heavy"
    +" cover of green leaves lie all about you here.  It is quiet here"
    +" amongst the trees-- almost too quiet.  The usual birds and woodland"
    +" creatures are conspicuously absent.  An east-west road lies just to"
    +" the south, while the forest continues on in many other directions."
     +"\n");

  add_exit(RHUN_DIR+"forest/k4","north",0);
  add_exit(RHUN_DIR+"forest/l4","northeast",0);
  add_exit(RHUN_DIR+"forest/l5","east",0);
  add_exit(RHUN_DIR+"forest/j5","west",0);
  add_exit(RHUN_DIR+"roads/section8/h","south",0);
  add_stuff();
}
