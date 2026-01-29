/*
   Pax Tharkas, wall level, Corner in gallery.

   gallery1.c
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

#define SGALL \
   ({   \
      WALL_LEVEL + "gallery5", \
   })

#define WGALL \
   ({   \
      WALL_LEVEL + "gallery4", \
      WALL_LEVEL + "gallery3", \
      WALL_LEVEL + "gallery2", \
   })


void
create_pax_room()
{
   set_short("Northeast corner in gallery");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"painting", "paintings"}), "This painting shows a " +
            "high mountain pass glittering in the light of the sun. " +
            "Snowfields flash among the peaks, and thick forests " +
            "cover the lower slopes. Many streams, swollen by ponds " +
            "and waterfalls, wind into the lowlands. A large band of " +
            "dwarves labors in the pass, building a low stone wall " +
            "across the pass.\n");


   add_exit(WALL_LEVEL + "gallery2", "west", 0);
   add_exit(WALL_LEVEL + "gallery5", "south", 0);
}


string
sgall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = SGALL;
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
        return ("Looking south you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The gallery to the south of you is empty. ");
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
   return ("Looking west you see that the gallery is empty. ");
}


string
room_descr()
{
   return "You are standing in the northeast corner of a very huge " +
          "gallery. The large room is chilly, exposed to the draft " +
          "from the outside by a number of very narrow slit windows " +
          "along the walls. " + sgall_descr() + wgall_descr() + "The " +
          "entire outer wall of the gallery is covered with large " +
          "paintings.\n";
}


construction()
{
   write("Sorry this are is under construction.. you can't go there.\n");
   return 1;
}
