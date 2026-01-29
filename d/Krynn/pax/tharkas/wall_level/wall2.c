/*
   Pax Tharkas, Wall level, the battlements of the great Tharkadan wall.

   wall2.c
   -------

   Coded ........: 95/03/06
   By ...........: Jeremiah

   Latest update : 95/03/10
   By ...........: Jeremiah

* Cotillion - 2020-09-29
* - Fixed type confusion
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
      WALL_LEVEL + "wall1", \
   })

#define WWALL \
   ({   \
      WALL_LEVEL + "wall3", \
   })


void
create_pax_room()
{
   set_short("Large gate");
   set_long("@@room_descr");

   INSIDE;

   add_exit(WALL_LEVEL + "wall3", "west", 0);
   add_exit(WALL_LEVEL + "wall1", "east", 0);
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
        return ("To the east you see " + COMPOSITE_LIVE(live) + ". ");
   }
   return ("The east part of the wall looks empty. ");
}


string
wwall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WWALL;
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
        return ("Looking west you see " + COMPOSITE_LIVE(live) + ". ");
   }
   return ("The west part of the wall is empty. ");
}


string
room_descr()
{
   return "You are standing on the battlements of the great Tharkadan " +
          "wall, right between the two towers of Pax Tharkas. The wall " +
          "stretches to both sides of you. " + wwall_descr() +
          ewall_descr() + "Looking north you see the narrow valley " +
          "leading up to the fortress. South you see the court yard, " +
          "lying in the shadows of the Kharolis mountains rising into " +
          "the sky.\n";
}

