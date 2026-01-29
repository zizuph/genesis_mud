/*
   Pax Tharkas, Ground level, Slave cavern.

   slave_cavern.c
   --------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/05/06
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

object quest_npc_robert;

void
reset_pax_room()
{
   if(objectp(quest_npc_robert))
      return;

   quest_npc_robert = clone_object(PMONSTER + "robert");
   quest_npc_robert->move_living("arrives", TO);
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Inside cavern");
   set_long("You are standing just inside a large dark cavern. In the " +
            "dim light flowing through cave entrance, you can see that " +
            "the floor is covered with dirty straw pallets. Here and " +
            "there black spots from small fires scars the cave floor. " +
            "Some wooden buckets stands near west side of the cave " +
            "entrance.\n"); 
	
   INSIDE;

   add_item(({"bucket", "buckets"}), "Rotten wooden buckets leaking " +
            "dirty water onto the cave floor. You hope nobody has to " +
            "drink that stuff.\n"); 

   add_item(({"pallet", "pallets"}), "Basically these are simple " +
            "straw filled mattresses, very thin, and of very poor " +
            "quality.\n");

   add_item(({"spot", "spots", "scar", "scars"}), "At several places " +
            "the floor has black spots, after small fires, probably " +
            "made to keep whoever lives in here warm.\n"); 

   add_exit(COURT_YARD + "court_yard3", "north", 0);
}
