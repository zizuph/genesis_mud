/*
   Pax Tharkas, Ground level, Corridor.

   corridor3.c
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

#define WCORR \
   ({   \
      GROUND_LEVEL + "corridor4", \
   })

#define ECORR \
   ({   \
      GROUND_LEVEL + "corridor2", \
      GROUND_LEVEL + "corridor1", \
   })



void
create_pax_room()
{
   add_the_lamp();

   set_short("Corridor");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "corridor2", "east", 0);
   add_exit(GROUND_LEVEL + "corridor4", "west", 0);
   add_exit(GROUND_LEVEL + "guard_room", "north", 0);
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
        return ("Looking west, down the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going west is empty. ");
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
        return ("In the corridor going east you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("There is nothing in the corridor going east. ");
}


string
room_descr()
{
   return "You are standing near the west end of a long east, west " + 
          "going corridor. " + wcorr_descr() + ecorr_descr() + 
          "The walls are made of closely fitted rocks, giving " +
          "them an appearance as if the corridor was carved into a " +
          "large rock. There's a wooden door in the north wall, the " +
          "door is open. A brass lamp provides the corridor " +
          "with a bright shining light.\n";
}
