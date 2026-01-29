/*
   Pax Tharkas, Ground level, Childrens playroom.

   playroom.c
   ----------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/05/30
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

void
create_pax_room()
{
   set_short("Childrens playroom");
   set_long("You are in a large room. This must be some kind of a " +
            "playroom. A few toys are lying around on the floor, " +
            "there's even an old rocking horse here. You notice, " +
            "that the southern half of the eastern wall looks " +
            "different from the rest of the walls. It looks like this " +
            "part has been rebuilt recently. A tunnel now leads east " +
            "replacing what ever was there before. A set of large " +
            "doors leads southwest.\n");
	
   INSIDE;

   add_item(({"toy", "toys"}), "Plain pieces of old toys, like farm " +
            "animals carved out of wood. A few wooden dolls, and " +
            "most conspicuous a wooden rocking horse.\n");

   add_item(({"horse", "rocking horse"}), "A wooden rocking horse, the " +
            "largest and finest piece of toy, among this old, sorry " +
            "collection of toys.\n");

   add_item(({"wall", "east wall", "eastern wall"}), "You examine the " +
            "eastern wall closer. It is very clear, that the southern " +
            "part of the wall, almost half of it, has been rebuild " +
            "recently. A tunnel now leads east.\n");

   add_item("tunnel", "This tunnel has been recently build into the " +
            "southern part of the eastern wall. The reason for this " +
            "isn't obvious. The tunnel leading east, has a size that " +
            "allows two men to walk upright and next to each other.\n");  

   add_item(({"door", "doors"}), "A set of large, sturdy looking, wooden " +
            "doors leading southwest from here, probably out of the " +
            "tower\n");

   add_exit(GROUND_LEVEL + "store_room", "east", 0);
   add_exit(GROUND_LEVEL + "corridor7", "north", 0);
   add_exit(COURT_YARD + "court_yard1", "southwest", 0);
   add_exit(GROUND_LEVEL + "nurseroom", "tunnel", 0);
}

