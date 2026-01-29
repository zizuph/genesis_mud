/*
   Pax Tharkas, Ground level, Court yard.

   court_yard3.c
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

#define NYARD \
   ({   \
      COURT_YARD + "court_yard2", \
      COURT_YARD + "court_yard1", \
   })


void
create_pax_room()
{
   set_short("South end of court yard");
   set_long("@@room_descr");
	
   OUTSIDE;

   add_exit(COURT_YARD + "court_yard2", "north", 0);
   add_exit(COURT_YARD + "slave_cavern", "south", 0);
   add_exit(COURT_YARD + "mountain_road1", "southwest", "@@upwards", 3);
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
room_descr()
{
   return "You are standing in the south end of a large court yard. " +
          "The court yard is lying in the shadows of the surrounding " +
          "mountains, rising high into the skies east, west and south " +
          "of you. North you see towers of Pax Tharkas rising above you. " +
          nyard_descr() + "South you see a large dark cave entrance. " +
          "A small mountain road leads southwest, upwards, from here.\n";
}


int
upwards()
{
   write("You drudge your way up the mountain road.\n");
   return 0;
}

