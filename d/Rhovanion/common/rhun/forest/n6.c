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
    +" east to west, while a road lies just off to the north."
     +"\n");

  add_exit(RHUN_DIR+"forest/m6", "west", 0);
  add_exit(RHUN_DIR+"forest/o6","east",0);
  add_exit(RHUN_DIR+"roads/section8/k","north",0);
  add_stuff();
}
