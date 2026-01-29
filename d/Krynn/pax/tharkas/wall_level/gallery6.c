/*
   Pax Tharkas, wall level, Gallery, 

   gallery6.c
   -----------

   Coded ........: 95/02/08
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

inherit PAXINROOM;

#define NGALL \
   ({   \
      WALL_LEVEL + "gallery4", \
   })



void
create_pax_room()
{
   set_short("Southwest corner in gallery");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"painting", "paintings"}), "This painting shows huge " +
            "dragons, red, blue, green, black and white, raging about " +
            "the towers of Pax Tharkas. Men - Knights of Solamnia - " +
            "mounted on other dragons are fighting back!!. The dragons, " +
            "the knights are riding, are beautiful dragons, gold, silver " +
            "and bronze, and the knights are carrying bright long lances " +
            "gleaming with a shining radiance. The metallic dragons are " +
            "driving the other dragons from the towers and walls. The " +
            "battlements are red with the blood from both attackers " +
            "and defenders.\n");
 
   add_exit(WALL_LEVEL + "gallery4", "north", 0);
   add_exit(WALL_LEVEL + "balcony1", "east", 0);
}


string
ngall_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = NGALL;
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
        return ("Looking north, along the gallery, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The gallery to the north of you is empty. ");
}


string
room_descr()
{
   return "You are standing in the southwest corner of a very huge " +
          "gallery. The large room is chilly, exposed to the draft " +
          "from the outside by a number of very narrow slit windows " +
          "along the walls. " + ngall_descr() + "The " +
          "entire outer wall of the gallery is covered with large " +
          "paintings. An open door leads east, out of the gallery.\n";
}
