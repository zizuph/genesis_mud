#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

object guard;

void reset_room()
{
  if(!objectp(guard))
  {
    reset_euid();
    guard=clone_object(RHUN_DIR+"npc/guard");
    guard->arm_me();
    guard->set_random_move(4);
    guard->set_restrain_path(RHUN_DIR+"ltown_ne");
    guard->move(TO,1);
  }
}

void create_room()
{
  set_short("By the wall");
  set_long("You stand beside the low stone wall surrounding"
    +" this large town.  Outside the town lie the plains"
    +" and the Sea of Rhun.  Off to the east, you can see a large, dark"
	+" forest.  The street lies just west of here.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st7","west",0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"plains","plains of rhun"}), 
     "The plains of Rhun in eastern Rhovanion stretch"
    +" out to the east for a ways.  Beyond them lies a gloomy-"
    +"looking forest.\n");
  add_item("forest", "The forest looks dark and rather"
    +" gloomy.  You can tell no further details from this distance.\n");
  add_item(({"sea", "sea of rhun"}), "The"
    +" Sea of Rhun, the largest known inland body of water, lies just"
    +" south of this large town.  It stretches off to the south and east"
    +" for as far as the eye can see.  You can just make out a couple of"
    +" ships and fishing boats out in the water.\n");

  reset_room();
}
