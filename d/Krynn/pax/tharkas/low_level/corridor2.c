/*
   Pax Tharkas, Low level, corridors 

   corridor2.c
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

#define WCORR \
   ({   \
      LOW_LEVEL + "corridor3", \
   })

#define ECORR \
   ({   \
      LOW_LEVEL + "corridor1", \
   })

#define SCORR \
   ({   \
      LOW_LEVEL + "corridor4", \
      LOW_LEVEL + "corridor6", \
   })


object door;

create_pax_room()
{
   add_the_lamp();   

   set_short("T-junction corridor in cellar");
   set_long("@@room_descr");

   INSIDE;
   
   add_exit(LOW_LEVEL + "corridor3", "west", 0);
   add_exit(LOW_LEVEL + "corridor1", "east", 0);
   add_exit(LOW_LEVEL + "corridor4", "south", 0);

   door = clone_object(POBJ + "prison_door2a");
   door->move(TO);
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
        return ("Down the eastern corridor you spot " +
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
        return ("In the corridor south you can see " +
                 COMPOSITE_LIVE(live) + ".\n");
   }
   return ("The corridor going south is empty.\n");
}


string
room_descr()
{
   return "You are standing at a T junction in the corridor. The " +
          "walls look solid, but here and there a little crack " +
          "reveal that they aren't. An iron oil lamp has been " +
          "mounted on the wall. The corridor goes west, east and " +
          "south. " + wcorr_descr() + ecorr_descr() + scorr_descr();
}


construction()
{
   write("This area has not yet been finished. come back later ?\n");
   return 1;
}
