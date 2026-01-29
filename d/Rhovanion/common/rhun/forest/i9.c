#include "def.h"
inherit THIS_DIR+"room";
#include "/d/Rhovanion/defs.h"

object woodcutter;

void reset_room()
{
  ::reset_room();

  if(!objectp(woodcutter))
  {
    reset_euid();
    woodcutter=clone_object(RHUN_DIR+"npc/woodcutter");
  }
  woodcutter->move(TO,1);
}

void create_room()
{
  set_short("Small clearing");
  set_long("This is a small clearing.  There are numerous"
     +" tree-stumps nearby; you guess a woodcutter has been hard at work."
     +"  The only exit is back through the trees to the east.\n");

  add_exit(RHUN_DIR+"forest/j9","east",0);

  add_item(({"tree","trees","stump","stumps","tree stump","tree stumps"}),
       "All that remains of the trees near here are"
      +" a few stumps.  A rather proficient"
      +" woodcutter has apparently been hard at work in this"
      +" area.\n");

  add_herbs();
  reset_room();
}
