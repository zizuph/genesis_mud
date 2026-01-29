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
    +"  The vast plains of Rhun stretch endlessly out to the north"
    +" from here, with nothing else in sight.  You may follow"
    +" along the wall to the east, or approach the city's"
    +" gate to the northwest.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/bywall3","east",0);
  add_exit(RHUN_DIR+"ltown_ne/streets/northgate", "northwest", 0);

  add_item("wall", "The town wall is made of stone, and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
add_item(({"plains", "plains of rhun"}), "The vast and empty plains"
    +" of Rhun in eastern Rhovanion stretch endlessly off to the"
    +" north for as far as the eye can see.\n");

  reset_room();
}