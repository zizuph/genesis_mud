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
     +" caused their silence.  To the south stands a small town."
     +"\n");

  add_exit(RHUN_DIR+"forest/l12","east",0);
  add_exit(RHUN_DIR+"forest/l11","northeast",0);
  add_exit(RHUN_DIR+"forest/k11","north",0);
  add_exit(RHUN_DIR+"stown5/crossroads","south",0);
  add_stuff();
}
