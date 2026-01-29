/*
   Pax Tharkas, Low level, corridors 

   corridor4.c
   ----------

   Coded ........: 95/01/07
   By ...........: Jeremiah

   Latest update : 95/03/02
   By ...........: Jeremiah

*/


inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define NCORR \
   ({   \
      LOW_LEVEL + "corridor2", \
   })

#define SCORR \
   ({   \
      LOW_LEVEL + "corridor6", \
   })


object door;

create_pax_room()
{
   add_the_lamp();

   set_short("Corridor in cellar");
   set_long("@@room_descr");

   INSIDE;

   add_item("shards", "These are the bits of broken bottles, It " +
            "looks like they once were liquor bottles. Most of " +
            "the bits are scattered along the western wall.\n");

   add_exit(LOW_LEVEL + "guard_room", "east", 0);
   add_exit(LOW_LEVEL + "corridor2", "north", 0);
   add_exit(LOW_LEVEL + "corridor6", "south", 0);
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
        return ("Looking north, up the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going north is empty. ");
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
        return ("Looking south you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going south is empty.\n");
}


string
room_descr()
{
   return "You are standing in a long north and south running " +
          "corridor. " + ncorr_descr() + scorr_descr() +
          "The corridor has been equipped with an iron oil " +
          "lamp hanging on the wall. " + 
          "Shards of broken bottles have been carelessly left on " +
          "the floor. There's a doorless opening leading east.\n";
} 

