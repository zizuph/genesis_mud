/*
   Pax Tharkas, Low level, corridors 

   corridor6.c
   ----------

   Coded ........: 95/01/07
   By ...........: Jeremiah

   Latest update : 95/04/27
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
      LOW_LEVEL + "corridor4", \
   })


create_pax_room()
{
   add_the_lamp();

   set_short("Corridor in cellar");
   set_long("@@room_descr");

   add_item(({"crack", "cracks"}), "Large cracks between the large " +
             "stones, of which the wall is build. Something violent " +
             "must have forced them apart.\n");

   INSIDE;
   
   add_exit(LOW_LEVEL + "corridor4", "north", 0);
   add_exit(LOW_LEVEL + "chamber_aghar", "south", 0);
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
room_descr()
{
   return "You are standing at the end of a long north and south running " +
          "corridor. The walls are build of greyish rock. There's a " +
          "few small cracks between the rocks. The cracks grow bigger " +
          "towards the southern end of the corridor. An iron lamp is " +
          "placed in a holder on the wall. " + ncorr_descr() +   
          "The corridor ends in an opening to the south.\n";
}


construction()
{
   write("This area has not yet been finished. come back later ?\n");
   return 1;
}

