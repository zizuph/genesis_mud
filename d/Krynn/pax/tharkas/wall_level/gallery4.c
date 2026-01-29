/*
   Pax Tharkas, wall level, Corner in gallery.

   gallery4.c
   -----------

   Coded ........: 95/02/08
   By ...........: Jeremiah

   Latest update : 17/05/31
   By ...........: Arman

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit PAXINROOM;

#define SGALL \
   ({   \
      WALL_LEVEL + "gallery6", \
   })

#define EGALL \
   ({   \
      WALL_LEVEL + "gallery1", \
      WALL_LEVEL + "gallery2", \
      WALL_LEVEL + "gallery3", \
   })


void
create_pax_room()
{
   set_short("Northwest corner in gallery");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"painting", "paintings"}), "@@painting_desc");

   add_exit(WALL_LEVEL + "gallery3", "east", 0);
   add_exit(WALL_LEVEL + "stairwell", "west", 0);
   add_exit(WALL_LEVEL + "gallery6", "south", 0);
}

string
painting_desc()
{
    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "canticle12"))
          {
            TP->catch_msg("\n\nAs you look at the painting you are provided with " +
                     "a divine revelation!\n\n\n");
            OOTS_ADD_REV(TP,"canticle12","edification - canticle of the dragon, verse 1 and 2");  
          }
    }

    return "This painting shows huge " +
           "dragons, red, blue, green, black and white, raging about " +
           "the towers of Pax Tharkas. Fire, lightning, acid and cold, " + 
           "rains down upon the courageous defenders, " +
           "driving them from the parapets to seek shelter within the " +
           "solid walls. Mighty dragons are landing on the towers of " +
           "the fortress. Pax Tharkas seems to be lost.\n";
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
        return ("Looking east, down the gallery, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("Looking east you see that the gallery is empty. ");
}


string
room_descr()
{
   return "You are standing in the northwest corner of a very huge " +
          "gallery. The large room is chilly, exposed to the draft " +
          "from the outside by a number of very narrow slit windows " +
          "along the walls. " + sgall_descr() + egall_descr() + "The " +
          "entire outer wall of the gallery is covered with large " +
          "paintings.\n";
}


construction()
{
   write("Sorry this are is under construction.. you can't go there.\n");
   return 1;
}
