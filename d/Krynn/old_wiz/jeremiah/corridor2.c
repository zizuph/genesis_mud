/*
   Pax Tharkas, Ground level, Corridor.

   corridor2.c
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
      GROUND_LEVEL + "corridor3", \
   })

#define ECORR \
   ({   \
      GROUND_LEVEL + "corridor1", \
   })


object door;

void
create_pax_room()
{
   add_the_lamp();

   set_short("Corridor");
   set_long("@@room_descr");
	
   INSIDE;

/*
   add_exit(GROUND_LEVEL + "corridor1", "east", 0);
   add_exit(GROUND_LEVEL + "corridor3", "west", 0);
   add_exit(GROUND_LEVEL + "throne_room", "south", 0);
   add_exit(GROUND_LEVEL + "stair_to_wl1", "up", 0);

   door = clone_object(POBJ + "cell_door1a");
   door->move(TO);
*/

   add_exit("/d/Krynn/jeremiah/cell", "north", 0);

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
   return ("The corridor going east is empty. ");
}


string
room_descr()
{
   return "You are standing near the east end in a long east, west " + 
          "going corridor. " + wcorr_descr() + ecorr_descr() + 
          "The walls are made of closely fitted rocks, giving " +
          "them an appearance as if the corridor was carved into a " +
          "large rock. A pair of tall wooden doors in the south wall " +
          "leads into another room. A flight of stairs leads up to " +
          "the next level. A brass lamp provides the corridor " +
          "with light.\n";
}

