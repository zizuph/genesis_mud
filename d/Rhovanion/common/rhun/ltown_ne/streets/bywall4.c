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
  set_long("The outer wall of this large town stands"
    +" nearby, low and sturdily constructed of grey stones."
    +"  Off to the east, you can see the road disappear into a dark"
    +" forest of tall trees that lies just beyond the plains to the"
    +" east.  The rest of town lies back to the west.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st4","west",0);

  add_item("wall", "The town wall is made of stone, and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item("forest", "The forest looks dark and rather"
    +" gloomy.  You can tell no further details from this distance.\n");
  add_item(({"plains","plains of rhun"}),
     "The plains head out to the east for a ways, before"
    +" being interrupted by a dark forest.\n");

  reset_room();
}
