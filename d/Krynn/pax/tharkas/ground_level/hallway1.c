/*
   Pax Tharkas, Ground level, Hallway in west tower.

   hallway1.c
   ----------

   Coded ........: 95/02/18
   By ...........: Jeremiah

   Latest update : 95/02/18
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
inherit PAXINROOM;

#define WHALL \
   ({   \
      GROUND_LEVEL + "hallway2", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("East end of hallway");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "hollow_wall3", "east", 0);
   add_exit(GROUND_LEVEL + "hallway2", "west", 0);
}


string
whall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WHALL;
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
        return ("In the west end of the hallway you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The west end of the hallway is empty. ");
}


string
room_descr()
{
   return "You are standing in the east end of a hallway. The walls " +
          "of the hallway are cold and bare. The floor is dirty and " +
          "marked by wear and tear. " + whall_descr() + "The exit from " +
          "the west tower is here. An iron lamp provides this part of " +
          "the hallway with light.\n";
}
