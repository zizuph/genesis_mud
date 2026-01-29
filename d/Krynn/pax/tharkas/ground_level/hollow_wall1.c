/*
   Pax Tharkas, Ground level, Hollow wall, entrance to east tower..

   hollow_wall1.c
   --------------

   Coded ........: 95/02/08
   By ...........: Jeremiah

   Latest update : 95/07/28
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define WWALL \
   ({   \
      GROUND_LEVEL + "hollow_wall2", \
      GROUND_LEVEL + "hollow_wall3", \
   })


void
create_pax_room()
{
   set_short("Entrance to east tower");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"hinge", "hinges"}), "Large metal hinges mounted solidly " +
            "in the stone roof. Apparently it is possible for the " +
            "ceiling to swing down. You are not sure you want to be in " +
            "here to see what happens if it does.\n"); 

   add_exit(GROUND_LEVEL + "hollow_wall2", "west", 0);
   add_exit(GROUND_LEVEL + "corridor6", "east", 0);
}


string
ewall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WWALL;
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
        return ("Looking west you can see " + COMPOSITE_LIVE(live) + ". ");
   }
   return ("The west part of the hollow wall looks empty. ");
}


string
room_descr()
{
   return "You are standing inside the hollow wall, known as the great " +
          "Tharkadan wall. The wall links the two towers of Pax Tharkas. " +
          "The wall stretches westward like a long corridor. Above you, " +
          "along the south ceiling, you see large hinges mounted in the " +
          "stone roof. " + ewall_descr() + "The entrance to the east " +
          "tower is here.\n";
}
