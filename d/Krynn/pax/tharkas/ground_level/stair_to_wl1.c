/*
   Pax Tharkas, Ground level, west end of staircase to wall_level.

   stair_to_wl1.c
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

#define ECORR \
   ({   \
      GROUND_LEVEL + "stair_to_wl2", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("Stairwell");
   set_long("@@room_descr");

   INSIDE;

   add_item(({"stair", "stairs"}), "These are solid stone stairs. The " +
            "stones of which this stair is build are fitted very " +
            "tightly together, giving the stair a look as if is was " + 
            "carved out of one piece rock.\n");

   add_exit(GROUND_LEVEL + "stair_to_wl2", "east", 0);
   add_exit(GROUND_LEVEL + "corridor2", "down",0);
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
        return ("In the east end of the small corridor you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The east end of the small corridor is empty. ");
}



string
room_descr()
{
   return "You are standing in a small narrow corridor between two " +
          "stairwells. " + ecorr_descr() + "The walls and stairs " +
          "look as if they were made of solid rock. On the wall a " +
          "small iron lamp flickers with a pale light. There's a " +
          "slight draft running along the corridor. The stairwell, " +
          "in this end of the corridor, leads down.\n";
}


void
do_flicker()
{
   tell_room(TO,"The pale light from the iron oil lamp flickers.\n");
}

