// Emerald/tmp/volcano/top.c
// creator: Triana (Nov 95)
// purpose: top of volcano
// note: 
// bugs:
// to-do: steam coming out, possible eruptions that do minor damage the higher you are the more you get, rocks falling as tells

#include "vol.h"
inherit VROOM;

create_volcano()
{
   set_short("Volcano Top");
	set_long("   At long last, you have reached the top of the volcano " +
         "As you look back across the territory you have covered, you are amazed you made " +
	"it this far. Steam and smoke billow from the top of the volcano " +
	"high up into the sky. The pathway you stand on is covered with cooled lava and rocks.\n\n");
   
	add_exit("v1.c", "northeast", 0, 6);
	add_exit("v4.c", "northwest", 0, 6);
	add_exit("v3.c", "southwest", 0, 6);
	add_exit("v2.c", "southeast", 0, 6);
 
   add_item(({"steam"}), "The hot steam comes from deep inside of the volcano which is fully of molten lava.  You wonder how long it has been since this one has erupted.\n");
   add_item(({"ashes"}), "The ashes run up and down the whole volcano, remenents of eruptions.\n");
   add_item(({"rocks"}), "Various sized rocks and pebbles litter the ground.\n");
 
   call_out("do_smoke", 30 + random(30));
}

do_smoke()
{
   tell_room(this_object(), "Smoke puffs from the volcano.\n");
   call_out("do_smoke", 30 + random(30));
}
