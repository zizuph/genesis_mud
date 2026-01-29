/*
   Pax Tharkas, wall level, Gallery.

   gallery3.c
   ----------

   Coded ........: 95/02/08
   By ...........: Jeremiah

   Latest update : 95/02/16
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

#define EGALL \
   ({   \
      WALL_LEVEL + "gallery1", \
      WALL_LEVEL + "gallery2", \
   })

#define WGALL \
   ({   \
      WALL_LEVEL + "gallery4", \
   })


void
create_pax_room()
{
   set_short("In a gallery");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"painting", "paintings"}), "This painting shows a " +
            "high mountain pass glittering in the light of the sun. " +
            "Snowfields flash among the peaks, and thinned out forests " +
            "cover the lower slopes. Many streams, swollen by ponds " +
            "and waterfalls, wind into the lowlands. In the pass you " +
            "you see two mighty stone towers linked by a massive stone " +
            "wall. Pax Tharkas in all its might!. On the slopes in " +
            "front of the fortress two curtain walls have been erected. " +
            "Humans, elves and dwarves, in shining armours, man the " +
            "battlements and the curtain walls.\n ");
             

   add_exit(WALL_LEVEL + "gallery2", "east", 0);
   add_exit(WALL_LEVEL + "gallery4", "west", 0);
   add_exit(WALL_LEVEL + "balcony1", "south", 0);
}


string
egall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = EGALL;
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
        return ("Looking east you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The gallery east of you is empty. ");
}


string
wgall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WGALL;
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
        return ("Looking west, down the gallery, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The gallery west of you is empty. ");
}


string
room_descr()
{
   return "You are standing in a very huge gallery. The large room " +
          "is chilly, exposed to the draft from the outside by a " +
          "number of very narrow slit windows along the walls. " + 
          egall_descr() + wgall_descr() + "The entire outer wall " + 
          "of the gallery is covered with large paintings. A door " +
          "leads south out of the gallery.\n";
}

