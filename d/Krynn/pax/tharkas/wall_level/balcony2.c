/*
   Pax Tharkas, Wall level, Balcony above throne room.

   balcony2.c
   ----------

   Coded ........: 95/02/16
   By ...........: Jeremiah

   Latest update : 95/07/27	
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

#define THRONE \
   ({   \
      GROUND_LEVEL + "throne_room", \
   })


create_pax_room()
{
   set_short("Balcony above throne room");
   set_long("@@room_descr");

   INSIDE;
   add_prop(ROOM_I_LIGHT, 1);

   add_item(({"throne", "dais", "mirror", "mirrors"}), "That is " +
            "in the room below you. You will have to go there if " +
            "want to have a closer look.\n");

   add_item("balcony", "A balcony high above another room. You are " +
            "standing on it. From here you can see everything " +
            "in the room below you. You will probably have to go " +
            "down there if you want a closer look at things though.\n");

   add_item(({"column", "columns"}), "Slender, but solid, stone " +
            "colums supporting the high ceiling.\n"); 

   add_exit(WALL_LEVEL + "balcony1", "west", 0);
}      


string
throne_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = THRONE;
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
        return (", to the west you can see " + COMPOSITE_LIVE(live) + ".\n");
   }
   return ".\n";
}


string
room_descr()
{
   return "You are standing on a kind of balcony above a large room. " +
          "Many slender columns support a high ceiling. Most of the " +
          "balcony is hidden in the shadows. Looking down you see a " +
          "large room furnished with every possible luxury. You are " +
          "sure that all that is beautiful, graceful, delicate and " +
          "valuable in the world, has been brought here to decorate this " +
          "room. A large ornate throne stands, raised above the floor on " +
          "a stone dais, in the south end of the room. Rare and " +
          "priceless silver mirrors hang on the walls. A pair of huge " +
          "open doors lead west" + throne_descr();
}


