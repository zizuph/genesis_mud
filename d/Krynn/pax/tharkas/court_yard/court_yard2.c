/*
   Pax Tharkas, Ground level, Court yard.

   court_yard2.c
   -------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/04/16
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

#define NYARD \
   ({   \
      COURT_YARD + "court_yard1", \
   })

#define SYARD \
   ({   \
      COURT_YARD + "court_yard3", \
   })


void
create_pax_room()
{
   set_short("Middle of court yard");
   set_long("@@room_descr");
	
   OUTSIDE;

   add_item(({"cave", "cave entrance", "entrance"}), "A strange, " +
            "flickering, red light seems to come from somewhere " +
            "within the cave. Hammering noises reaches you from the " +
            "cave entrance.\n");

   add_exit(COURT_YARD + "court_yard1", "north", 0);
   add_exit(COURT_YARD + "court_yard3", "south", 0);
   add_exit(COURT_YARD + "mill_cavern1", "east", 0);
}


string
nyard_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = NYARD;
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
        return ("Looking north, in the court yard, you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The court yard north of you is empty. ");
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
        return ("In the south end of the court yard you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("There is no one in the court yard south of you. ");
}


string
room_descr()
{
   return "You are standing in the middle of a large court yard. " +
          "The court yard is lying in the shadows of the surrounding " +
          "mountains, rising high into the skies east, west and south " +
          "of you. North the towers of Pax Tharkas looms above you, " +
          "casting their shadows into the courtyard around you. " +
          nyard_descr() + syard_descr() + "East there is a large " +
          "cave entrance. The entrance seems to glow with an eerie, " +
          "flickering, red light.\n";          
}


