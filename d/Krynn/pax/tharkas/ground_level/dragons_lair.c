/*
   Pax Tharkas, Ground level, Dragons lair. The lair of Ember.
                It is from here Lord Verminaard mounts his dragon.

   dragons_lair.c
   --------------

   Coded ........: 95/02/01
   By ...........: Jeremiah

   Latest update : 95/07/27
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define BALC \
   ({   \
      WALL_LEVEL + "balcony1", \
   })

void
create_pax_room()
{
   set_short("Tall dark shaft");
   set_long("You find yourself standing on a narrow ledge in front " +
            "of a deep pit. Below you the room is lost in darkness, " +
            "making it impossible to guess how far down the bottom would " +
            "be. A fall from here could be lethal. Above you the room " +
            "stretches like a vertical tunnel several storeys high. " +
            "A balcony lines the north wall about one storey up. The " +
            "balcony is almost totally hidden in dark shadows. " +
            "Far up above you, you can see that the room has no roof, " +
            "but leads up, and out, into the free air. There's a foul " +
            "smell rising from the pit. You can't help the feeling of " +
            "fear sneaking up on you.\n");            
	
   INSIDE;

   add_item("ledge", "The ledge, on which you are standing, isn't wider " +
            "than two or three feet. Deep marks are drawn in the stone " +
            "ledge, as if some huge claws has grasped at the edge of the " +
            "narrow ledge. You don't feel comfortable standing " +
            "here at all.\n");

   add_item("pit", "You look down into darkness. You cannot figure out " +
            "how far below you the bottom of the pit is. A foul smell " +
            "like rotting meat evades the deep darkness of the pit.\n");

   add_item("balcony", "@@balcony_descr");

   add_exit(GROUND_LEVEL + "throne_room", "east", 0);
}


string
balcony_descr()
{
   string *roomfiles;
   string ret_str;
   object *inv, room;
   int    i;

   roomfiles = BALC;
   ret_str = "Taking a closer look at the balcony above you, ";
   inv = ({});

   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }

   if (sizeof(inv) == 0)
      ret_str += "you see nothing.";

   if (sizeof(inv) == 1)
      ret_str += "you see a figure standing in the shadows. You " +
                 "cannot see who or what it is.";

   if (sizeof(inv) > 1)
      ret_str += "you see some figures standing in the shadows. " +
                 "You cannot see who or what they are.";

   ret_str += "\n";
   return ret_str;
}
