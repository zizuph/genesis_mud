/*
   Pax Tharkas, Ground level, east end of staircase to wall_level.

   stair_to_wl2.c
   --------------

   Coded ........: 95/01/29
   By ...........: Jeremiah

   Latest update : 95/02/09
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
      GROUND_LEVEL + "stair_to_wl1", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("Corridor in stairwell");
   set_long("@@room_descr");

   INSIDE;

   add_item(({"stair", "stairs"}), "These are solid stone stairs. The " +
            "stones of which this stair is build are fitted very " +
            "tightly together, giving the stair a look as if is was " + 
            "carved out of one piece rock.\n");

   add_exit(GROUND_LEVEL + "stair_to_wl1", "west", 0);
   add_exit(WALL_LEVEL + "gallery5", "up",0);
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
        return ("In the west end of the small corridor you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The west end of the small corridor is empty. ");
}



string
room_descr()
{
   return "You are standing in a small narrow corridor between two " +
          "stairwells. " + wcorr_descr() + "The walls and stairs " +
          "are made of dark stone. On the wall a small iron lamp " +
          "flickers in the slight draft coming from above. The stairwell, " +
          "in this end of the corridor, leads up.\n";
 
}


void
do_flicker()
{
   tell_room(TO,"The light from the iron oil lamp flickers slightly.\n");
}

