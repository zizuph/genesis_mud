/*
   Pax Tharkas, Wall level, On the parapets of the great Tharkadan wall 
                entrance to west tower.

   wall3.c
   -------

   Coded ........: 95/03/06
   By ...........: Jeremiah

   Latest update : 95/03/10
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
      WALL_LEVEL + "wall2", \
      WALL_LEVEL + "wall1", \
   })


void
create_pax_room()
{
   set_short("Entrance to west tower");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(WALL_LEVEL + "stair_to_wtow1", "west", 0);
   add_exit(WALL_LEVEL + "wall2", "east", 0);
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
        return ("Looking east, along the wall, you can see " + 
                COMPOSITE_LIVE(live) + ". ");
   }
   return ("The east part of the wall looks empty. ");
}


string
room_descr()
{
   return "You are standing on the battlements of the great Tharkadan " +
          "wall. The wall links the two towers of Pax Tharkas. The wall " +
          "stretches east towards the western tower. " + ewall_descr() +
          "The entrance to the west tower is here. Looking north you see " +
          "the narrow valley leading up to the fortress. South you see " +
          "the court yard, lying in the shadows of the Kharolis " +
          "mountains rising into the sky.\n";
}
