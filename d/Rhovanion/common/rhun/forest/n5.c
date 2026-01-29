#include "def.h"
inherit THIS_DIR+"inside";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("In the forest");
  set_long("You are within a large forest in Rhun.  Thick tree-"
     +"trunks stand all about you.  The ground is covered with fallen leaves"
     +" and the occassional rotten log.  But there is almost no sound here: no"
     +" chirping of birds, nor call of other animals.  You wonder what has"
     +" caused their silence."
     +"\n");

  add_exit(RHUN_DIR+"forest/m5","west",0);
  add_exit(RHUN_DIR+"forest/m4","northwest",0);
  add_exit(RHUN_DIR+"forest/o5","east",0);
  add_stuff();
}
