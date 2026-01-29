/*
   Pax Tharkas, Ground level, Hallway in west tower.

   hallway2.c
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

#define EHALL \
   ({   \
      GROUND_LEVEL + "hallway1", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("West end of hallway");
   set_long("@@room_descr");
	
   INSIDE;

   add_item("furniture", "Broken pieces of furniture. These are the " +
            "unusable remains of a table and a few chairs.\n");

   add_exit(GROUND_LEVEL + "mess_hall1", "north", 0);	
   add_exit(GROUND_LEVEL + "hallway1", "east", 0);
   add_exit(GROUND_LEVEL + "guard_room1", "west", 0);
}


string
ehall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = EHALL;
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
        return ("Looking down the hallway you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The east end of the hallway is empty. ");
}


string
room_descr()
{
   return "You are standing in the west end of a short hallway. The walls " +
          "of the hallway are cold and bare. The floor is dirty and " +
          "marked by wear and tear. " + ehall_descr() + "A few pieces of " +
          "wrecked furniture lies here. A small iron lamp shines from its " +
          "place on the wall. A door leads further west, and a double door " +
          "leads north.\n"; 
}
