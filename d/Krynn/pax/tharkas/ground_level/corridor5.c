/*
   Pax Tharkas, Ground level, Corridor, entrance from low_level.

   corridor5.c
   -----------

   Coded ........: 95/01/11
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

#define WCORR \
   ({   \
      GROUND_LEVEL + "corridor6", \
   })

#define NCORR \
   ({   \
      GROUND_LEVEL + "corridor4", \
   })

#define SCORR \
   ({   \
      GROUND_LEVEL + "corridor7", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("T-junction corridor");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "corridor6", "west", 0);
   add_exit(GROUND_LEVEL + "corridor4", "north", 0);
   add_exit(GROUND_LEVEL + "corridor7", "south", 0);
   add_exit(LOW_LEVEL + "stair_to_gl", "down", 0);
}


string
wcorr_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WCORR;
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
        return ("Looking west, along the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going west is empty. ");
}


string
ncorr_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = NCORR;
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
        return ("North, in the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor to the north is empty. ");
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
        return ("Looking south, down the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going south is empty. ");
}


string
room_descr()
{
   return "You are standing at a T junction in a bright corridor. " +
          "A brass oil lamp is hanging on the east wall. " +
          wcorr_descr() + ncorr_descr() + scorr_descr() +
          "A flight of narrow stairs lead down into dimness.\n";
}
