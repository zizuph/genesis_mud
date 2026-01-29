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
  set_long("The outer wall of this large town stands"
    +" nearby, low and sturdily constructed of grey stones."
    +"  Off to the north stands the River Carnen, rushing south and east"
    +" to empty into the Sea of Rhun.  Beyond it stand the plains, "
    +"stretching out seemingly endlessly.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st4","southwest",0);

  add_item("wall", "The town wall is made of stone, and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"plains","plains of rhun"}), 
         "The plains stretch out to the north beyond the"
	+" River Carnen.\n");
  add_item(({"river","river carnen","carnen"}), 
     "The River Carnen rushes by on its way down from"
    +" the Iron Hills in the far north toward its resting place, "
    +"the Sea of Rhun.\n");

  reset_room();
}