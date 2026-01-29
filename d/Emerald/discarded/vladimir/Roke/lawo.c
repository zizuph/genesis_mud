inherit "/std/room.c";

#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"
#include <macros.h>

string long;
object guard, guard;

create_room()
{
   set_short("Jail house");
   set_long(
      "You have entered Cove's new law enforcement office. The jail\n"
      + "cells are to your east, blocked by a metal gate. To your\n"
      + "north is a door held open by a large stone. \n"
      + "On the "
      + "floor is a large wool rug that covers most of the room.\n"
      + "You feel very safe here.\n");
   add_item(({"cells", "jail cells"}), "They look quite full at the moment.\n");
   add_item(({"door"}), "It is held open by a very heavy stone.\n");
   add_item(({"gate", "metal gate"}), "The gate is of finest steel, "+
      "made to last a long time.\n");
   add_item(({"stone", "large stone"}), "It is quite heavy.\n");
   add_item(({"rug", "wool rug"}), "This is a large rectangular rug "+
      "made from wool. It is plain off-white. It seems to be "+
      "nailed to the ground.\n");
   add_item(({"guard", "pacing guard"}), "You peer through the bars "+
      "at the guard and notice he is holding his sword tightly "+
      "to his side.\n"
      + "He notices you and says: Leave before I put you in here, "+
      "dirtbag.\n");
   
   add_cmd_item("permission","request", "You attempt to convince the "+
      "guard to allow you to pass. Unfortunately, he will not let you in.\n");
   add_exit("/d/Roke/vladimir/omarshal", "north", "@@block");
   add_exit("/d/Roke/vladimir/cells", "east","@@gate");
   add_exit("/d/Roke/varl/atuan/cape/cove9", "south");
   add_prop(ROOM_I_INSIDE, 1);
   reset_room();
}

reset_room()
{
   if(!guard)
   {
      guard = clone_object("/d/Roke/vladimir/monsters/enforcer");
	  guard->move(TO);
   }

}

gate()
{
   write("The gate is locked.\n");
   return 1;
}

int block()
{
        if(MAL("officer") && !TP->query_invis())
	{
		write("You feebly attempt to pass through the guard without "+
			"requesting permission first. You are shoved backwards "+
			"with sheer force.\n");
		say(QCTNAME(TP)+" attempts to pass north, but is shoved back\n"+
			"violently by the guard.\n");
		return 1;
	}
        else if (MAL("officer"))
	{
		write("The guard sees you.\n");
		write("You feebly attempt to pass through the guard without "+
			"requesting permission first. You are shoved backwards "+
			"with sheer force.\n");
		say(QCTNAME(TP)+" attempts to pass north, but is shoved back\n"+
			"violently by the guard.\n");
		return 1;
	}
	return 0;
}

