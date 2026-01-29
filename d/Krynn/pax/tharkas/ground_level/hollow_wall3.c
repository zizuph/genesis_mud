/*
   Pax Tharkas, Ground level, Hollow wall, entrance to west tower..

   hollow_wall3.c
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

#define EWALL \
   ({   \
      GROUND_LEVEL + "hollow_wall2", \
      GROUND_LEVEL + "hollow_wall1", \
   })


void
create_pax_room()
{
   set_short("Entrance to west tower");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"hinge", "hinges"}), "Large metal hinges mounted solidly " +
            "in the stone roof. Apparently it is possible for the " +
            "ceiling to swing down. You are not sure you want to be in " +
            "here to see what happen if it does.\n");

   add_exit(GROUND_LEVEL + "hollow_wall2", "east", 0);
   add_exit(GROUND_LEVEL + "hallway1", "west", "@@construction");
}


string
ewall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = EWALL;
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
        return ("Looking east along the hollow wall you see " + 
                COMPOSITE_LIVE(live) + ". ");
   }
   return ("To the east, the hollow wall is empty. ");
}


string
room_descr()
{
   return "You are standing inside the hollow wall, known as the great " +
          "Tharkadan wall. The wall links the two towers of Pax Tharkas. " +
          "The wall stretches eastward like a long corridor. Above you, " +
          "along the south ceiling, you see large hinges mounted in the " +
          "stone roof. " + ewall_descr() + "The entrance to the west " +
          "tower is here.\n"; 

}
