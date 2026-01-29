/*
   Pax Tharkas, Ground level, Corridor.

   corridor4.c
   -----------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/03/02
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit "/d/Krynn/pax/tharkas/misc/Blamp_base";
inherit PAXINROOM;

#define ECORR \
   ({   \
      GROUND_LEVEL + "corridor3", \
      GROUND_LEVEL + "corridor2", \
      GROUND_LEVEL + "corridor1", \
   })

#define SCORR \
   ({   \
      GROUND_LEVEL + "corridor6", \
      GROUND_LEVEL + "corridor7", \
   })



void
create_pax_room()
{
   add_the_lamp();

   set_short("Corner in corridor");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "corridor3", "east", 0);
   add_exit(GROUND_LEVEL + "corridor5", "south", 0);
   add_exit(GROUND_LEVEL + "reception", "west", 0);
   add_exit(GROUND_LEVEL + "kitchen", "north", 0);
}


string
ecorr_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = ECORR;
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
        return ("Looking east, down the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going east is empty. ");
}


string
scorr_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = SCORR;
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
        return ("In the southern corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going south is empty. ");
}


string
room_descr()
{
   return "You are standing at a corner in a long corridor. The " +
          "corridor continues east and south from here. " + ecorr_descr() +
          scorr_descr() + "There's an open door leading west and " +
          "another leading north. A strange smell comes from the door to " +
          "the north. A small oil lamp, hanging on the wall, fills the " +
          "room with ample light.\n";
}
