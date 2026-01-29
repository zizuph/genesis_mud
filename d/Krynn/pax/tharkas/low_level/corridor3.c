/*
   Pax Tharkas, Low level, corridors 

   corridor3.c
   ----------

   Coded ........: 95/01/07
   By ...........: Jeremiah

   Latest update : 95/03/09
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

#define ECORR \
   ({   \
      LOW_LEVEL + "corridor1", \
      LOW_LEVEL + "corridor2", \
   })

#define SCORR \
   ({   \
      LOW_LEVEL + "corridor5", \
   })


object door;

create_pax_room()
{
   add_the_lamp();

   set_short("Corridor in cellar");
   set_long("@@room_descr");

   INSIDE;

   add_exit(LOW_LEVEL + "store_room1", "west", 0);
   add_exit(LOW_LEVEL + "corridor2", "east", 0);
   add_exit(LOW_LEVEL + "corridor5", "south", 0);
   
   door = clone_object(POBJ + "prison_door3a");
   door->move(TO);
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
        return ("In the corridor south you spot " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going south is empty. ");
}


string
room_descr()
{
   return "You are standing in a filthy corridor. The walls are made " +
          "grey rock. A small lamp has been fastened to the wall. " + 
          "The corridor continues east and south. " + ecorr_descr() +
           scorr_descr() + "There's an opening leading west.\n";
}

   
construction()
{
   write("This area has not yet been finished. come back later ?\n");
   return 1;
}

