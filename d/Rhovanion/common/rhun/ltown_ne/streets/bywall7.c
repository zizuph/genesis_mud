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
  set_long("You stand just inside the low stone wall sur"
    +"rounding this large town.  Outside, the River Carnen rushes"
    +" southeast to meet with"
    +" the Sea of Rhun just south of here.  The city streets"
    +" lie back to the northeast.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st6","northeast",0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"sea", "sea of rhun"}), "The"
    +" Sea of Rhun, the largest known inland body of water, lies just"
    +" south of this large town.  It stretches off to the south and east"
    +" for as far as the eye can see.  You can just make out a couple of"
    +" ships and fishing boats out in the water.\n");
  add_item(({"river", "river carnen", "carnen"}), "The"
    +" River Carnen lies west and north of the town.  It flows down"
    +" all the way from the Iron Hills,  joined halfway down by the"
    +" River Celduin from Mirkwood and Esgaroth, to empty into the"
    +" Sea of Rhun.  Ships travel regularly up and down the river,"
    +" heading from a smaller nearby town up to the Lake Town of"
    +" Esgaroth, making one stop halfway upriver on the way.\n");

  reset_room();
}
