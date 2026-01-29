/*
   Pax Tharkas, Low level, corridors 

   corridor1.c
   ----------

   Coded ........: 95/01/07
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

inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
inherit PAXINROOM;

#define WCORR \
   ({   \
      LOW_LEVEL + "corridor2", \
      LOW_LEVEL + "corridor3", \
   })

   
object door;

void
create_pax_room()
{
   add_the_lamp();

   set_short("Corridor in cellar");
   set_long("@@room_descr");

   INSIDE;  

   add_exit(LOW_LEVEL + "corridor2", "west", 0);
   add_exit(LOW_LEVEL + "rubbles1", "east" ,0);

   door = clone_object(POBJ + "prison_door1a");
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
                 COMPOSITE_LIVE(live) + ".\n");
   }
   return ("The corridor going west is empty.\n");
}


string
room_descr()
{
   return "You are standing in a dimly lit corridor. The walls are " +
          "made of greyish stones fitted very close together. There are " +
          "almost no cracks between the stones. An iron lamp on the wall " +
          "throws a faint light across the corridor. " +
          "An old wooden door leads east and the corridor continues " +
          "west. " + wcorr_descr();
}

