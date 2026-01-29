/*
   Pax Tharkas, wall level, Gallery.

   gallery2.c
   -----------

   Coded ........: 95/02/08
   By ...........: Jeremiah

   Latest update : 95/02/15
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
   })

#define WGALL \
   ({   \
      WALL_LEVEL + "gallery4", \
      WALL_LEVEL + "gallery3", \
   })


void
create_pax_room()
{
   set_short("Corner in gallery");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"painting", "paintings"}), "This painting shows a " +
            "high mountain pass glittering in the light of the sun. " +
            "Snowfields flash among the peaks, and thick forests " +
            "cover the lower slopes. Many streams, swollen by ponds " +
            "and waterfalls, wind into the lowlands. A large band of " +
            "dwarves, humans and elves, labors in the pass, building " +
            "a solid stone wall across the pass. The wall reaches " +
            "several stories into the air. At each end of the wall, " +
            "almost leaning against the mountain sides, two mighty towers " +
            "are inching their way into the sky. Elves appear from " +
            "the forests bearing huge logs on low wagons.\n");

   add_exit(WALL_LEVEL + "gallery1", "east", 0);
   add_exit(WALL_LEVEL + "gallery3", "west", 0);
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
   return ("The gallery to the east of you is empty. ");
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
   return ("Looking west you see that the gallery that way is empty. ");
}


string
room_descr()
{
   return "You are standing in a very huge gallery. The large room " +
          "is chilly, exposed to the draft from the outside by a " +
          "number of very narrow slit windows along the walls. " + 
          egall_descr() + wgall_descr() + "The entire outer wall of " +
          "the gallery is covered with large paintings.\n";
}


construction()
{
   write("Sorry this are is under construction.. you can't go there.\n");
   return 1;
}
