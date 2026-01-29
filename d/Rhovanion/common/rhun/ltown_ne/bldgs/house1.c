#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

object woman,child;

void reset_room()
{
  seteuid(getuid());
  if(!objectp(woman))
  {
    woman=clone_object(RHUN_DIR+"npc/poorwoman");
    woman->move(TO,1);
  }
  if(!objectp(child))
  {
    child=clone_object(RHUN_DIR+"npc/poorchild");
    child->move(TO,1);
  }
}

void create_room()
{
  set_short("Small home");
  set_long("You have stepped into a small home in this tiny"
	+" town.  The walls are hewn of wooden logs, and the"
	+" ceiling thatched.  A few scattered bits of furniture are here--"
	+" a bed, chair and table, for the most part.  The resident of"
	+" this tiny estate is obviously quite poor.  The only"
        +" exit is back out a small open doorway to the southeast.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st2","southeast",0);

  add_prop(ROOM_I_INSIDE,1);

  add_item(({"furniture","bed","table","chair","chairs"}), "The"
	+" furniture which adorns this humble abode is all made"
	+" from wood.  It is of no interest to you.\n");

  reset_room();
}
