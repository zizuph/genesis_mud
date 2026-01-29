/*
   Pax Tharkas, Ground level, Corridor, exit to hollow wall.

   corridor6.c
   -----------

   Coded ........: 95/01/23
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

inherit "/d/Krynn/pax/tharkas/misc/Blamp_base";
inherit PAXINROOM;

#define ECORR \
   ({   \
      GROUND_LEVEL + "corridor5", \
   })


void
create_pax_room()
{
   add_the_lamp();

   set_short("Exit to hollow wall");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "corridor5", "east", 0);
   add_exit(GROUND_LEVEL + "hollow_wall1", "west", 0);
   add_exit(GROUND_LEVEL + "reception", "north", 0);
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
        return ("Looking east, back down corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor going east is empty. ");
}


string
room_descr()
{
   return "You are at the end of a corridor. The grey stone walls look " +
          "as if they were made of one large piece. A door leads west " +
          "out of the tower, and an open door leads north. " + ecorr_descr() +
          "A small brass oil lamp fills the room with light.\n";
}
