/*
   Pax Tharkas, Ground level, Corridor.

   corridor1.c
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

inherit PAXINROOM;
inherit "/d/Krynn/pax/tharkas/misc/Blamp_base";

#define WCORR \
   ({   \
      GROUND_LEVEL + "corridor4", \
      GROUND_LEVEL + "corridor3", \
      GROUND_LEVEL + "corridor2", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("End of corridor");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "corridor2", "west", 0);
   add_exit(GROUND_LEVEL + "private_quarters", "south", 0);
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
        return ("Looking west, down the long corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The long corridor going west is empty. ");
}


string
room_descr()
{
   return "You are at the east end of a long corridor. " + 
          wcorr_descr() + "A doorway leads south from here, into a room. " +
          "The grey stone walls along the corridor are bare, cold " +
          "and uninviting. " +
          "A brass oil lamp fills the corridor with light.\n";
}

