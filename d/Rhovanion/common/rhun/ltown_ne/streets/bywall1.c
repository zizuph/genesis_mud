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
    +" this large town.  Outside the town lie the plains of Rhun"
    +" and the swiftly-flowing River Carnen as it heads toward"
    +" the Sea of Rhun.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/northgate","northeast",0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"plains", "plains of rhun"}), 
     "The plains of Rhun in eastern Rhovanion stretch"
    +" out to the north, seemingly endless.\n");
  add_item(({"river","carnen","river carnen"}), "The"
    +" River Carnen lies just to the west, and flows down toward the"
    +" Sea of Rhun in the southeast.\n");

  reset_room();
}
