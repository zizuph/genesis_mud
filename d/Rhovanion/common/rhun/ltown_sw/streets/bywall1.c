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
    +" this large town.  Outside the town lie the plains of Rhun, "
    +"stretching endlessly on.  The wall continues to the south.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/westgate","northeast",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/bywall2","south",0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for defence.\n");
  add_item(({"plains","plains of rhun"}), 
     "The plains of Rhun in eastern Rhovanion stretch"
    +" out to the north, seemingly endless.\n");

  reset_room();
}
