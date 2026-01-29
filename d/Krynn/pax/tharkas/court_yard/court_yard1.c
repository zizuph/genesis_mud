/*
   Pax Tharkas, Ground level, Court yard.

   court_yard1.c
   -------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/04/12
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

#define SYARD \
   ({   \
      COURT_YARD + "court_yard2", \
      COURT_YARD + "court_yard3", \
   })


void
create_pax_room()
{
   set_short("North end of court yard");
   set_long("@@room_descr");
	
   OUTSIDE;

   add_exit(GROUND_LEVEL + "hollow_wall2", "north", 0);
   add_exit(COURT_YARD + "court_yard2", "south", 0);
   add_exit(GROUND_LEVEL + "playroom", "northeast", 0);
}


string
syard_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = SYARD;
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
        return ("Looking south, in the court yard, you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The court yard south of you is empty. ");
}


string
room_descr()
{
   return "You are standing in the north end of a large court yard. " +
          "The court yard is lying in the shadows of the surrounding " +
          "mountains, rising high into the skies east, west and south " +
          "of you. North the towers of Pax Tharkas looms above you, " +
          "casting their shadows into the courtyard around you. " + 
          syard_descr() + "There is an entrance, to the north, into " +
          "the hollow Tharkadan wall connecting the mighty towers. A " +
          "set of large wooden doors leads northeast, into the east " +
          "tower.\n"; 
}

