#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

object *guard;

void reset_room()
{
  int i;

  seteuid(getuid());
  for(i=0; i<4; i++)
    if(!objectp(guard[i]))
    {
      guard[i]=clone_object(RHUN_DIR+"npc/guard");
      guard[i]->arm_me();
      guard[i]->move(TO,1);
    }
}

void create_room()
{
  set_short("Guard house");
  set_long("You stand in a guard house in this rather"
	+" large town near the Sea of Rhun.  The entire building--"
	+" quite large and spacious-- is made of wood.  This"
	+" is obviously a resting place for the town guards."
	+"  The street lies back to the east.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st6","east",0);

  add_prop(ROOM_I_INSIDE,1);
  guard=allocate(4);
  reset_room();
}