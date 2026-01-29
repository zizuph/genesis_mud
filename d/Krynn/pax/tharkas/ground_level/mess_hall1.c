/*
   Pax Tharkas, Ground level, Mess hall in west tower.

   mess_hall1.c
   ------------

   Coded ........: 95/03/02
   By ...........: Jeremiah

   Latest update : 95/03/27
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

#define NHALL \
   ({   \
      GROUND_LEVEL + "mess_hall2", \
   })


void
create_pax_room()
{
   set_short("South end of mess hall");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"fireplace", "fireplaces"}), "There are four large " +
            "fireplaces. one in each corner of this large mess hall. " +
            "A large fire flickers in each of the fireplaces.\n");

   add_item(({"table", "tables"}), "These are long wooden tables of a " +
            "simple but functional design. They are standing scattered " +
            "in an unorderly way all over the mess hall.\n");

   add_item(({"bench", "benches"}), "Long low benches placed along the " +
            "the many tables tables in here. Two at each table.\n"); 

   add_exit(GROUND_LEVEL + "mess_hall2", "north", 0);	
   add_exit(GROUND_LEVEL + "hallway2", "south", 0);
}


string
nhall_descr()
{
   string *roomfiles;
   object *inv, *live, room;	
   int i;

   roomfiles = NHALL;
   inv = ({});

   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }

   if (inv && sizeof(inv) > 0)
   {
     live = FILTER_LIVE(inv);
     if (sizeof(live) > 0)
        return ("In the north end of the mess hall you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The north end of the mess hall is empty. ");
}


string
room_descr()
{
   return "You are standing in the south end of a large mess hall. " +
          nhall_descr() + "There is a large fireplace in each corner " +
          "of this room. All over the room long tables and benches " +
          "are scattered in an unorderly way. The air in here smells " +
          "of foul food and cheap ale. A thin carpet of smoke from the " +
          "fireplaces hangs in the air.\n"; 
}
