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
    guard->set_restrain_path(RHUN_DIR+"ltown_sw");
    guard->move(TO,1);
  }
}

void create_room()
{
  set_short("By the wall");
  set_long("You stand beside the low stone wall surrounding"
    +" this large town.  Outside the town lies the vast expanse of"
    +" the Sea of Rhun.  The street is back to the west.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st9","west",0);

  add_item(({"sea","sea of rhun"}), "The"
    +" Sea of Rhun stretches on to the east and south, its far shores"
	+" beyond the ranger of sight.\n");

  reset_room();
}
