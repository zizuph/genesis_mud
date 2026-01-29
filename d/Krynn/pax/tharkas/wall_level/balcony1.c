/*
   Pax Tharkas, Wall level, Balcony above dragons lair.

   balcony1.c
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

#define LAIR \
   ({   \
      GROUND_LEVEL + "dragons_lair", \
   })


create_pax_room()
{
   set_short("Balcony above pit");
   set_long("@@room_descr");

   add_item(({"ledge", "pit", "doors"}), "That is in the room " +
            "below you. You will have to, somehow, go there if " +
            "want to take a closer look.\n");

   add_item("balcony", "A balcony high above another room. You are " +
            "standing on it. From here you can see everything " +
            "in the room below you. You will probably have to go " +
            "down there if you want a closer look at things though.\n");

   add_item(({"column", "columns"}), "Slender and solid stone " +
            "colums supporting the high ceiling.\n");

   INSIDE;

   add_prop(ROOM_I_LIGHT, 1);

   add_exit(WALL_LEVEL + "balcony2", "east", 0);
   add_exit(WALL_LEVEL + "gallery6", "west", 0);   
   add_exit(WALL_LEVEL + "gallery3", "north", 0);
}      


string
lair_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = LAIR;
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
        return ("On the ledge below you, you see " +
                COMPOSITE_LIVE(live) + ".");
   }
   return "";
}


string
room_descr()
{
   return "You are standing on a kind of balcony above a deep dark pit. " +
          "Many slender columns support a high ceiling. Most of the " +
          "balcony is hidden in the shadows. Looking down you see a " +
          "faint light, coming from a pair of huge doors, falling on " +
          "a narrow ledge in front of a deep pit. Below the ledge the " +
          "room is lost in darkness, making it impossible to guess how " + 
          "far down the bottom would be. A fall from there could be " +
          "lethal. Not to mention a fall from this balcony. Above you the " +
          "room stretches like a vertical tunnel several storeys high. " +
          "Far up above you, you can see that the room has no roof, " +
          "but leads out into the free air. " + lair_descr() + "\n";
}
