/*
 * Main12.c
 * Tunnel room in the caverns beneath the island.
 * Leads east to guard room and south further into caves.
 *   - Alaron September 13, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
   set_short("North Hall");
   set_long("   Light pours into this section of the cavern from what "+
	    "looks like a small chamber to the northwest. Gloomy, dark "+
	    "and forboding passageways lead off to the south and east "+
	    "through hidden and winding tunnels. You notice water dripping "+
	    "from the ceiling and turning into little streams on the "+
	    "cave floor. A foul, stagnant odor dominates the area, combining "+
	    "with the stale, old odor of ancient dampness and mildew.\n\n");

   add_item("light",
	    "The light to the northwest is far too painful to look at "+
	    "while standing here in the relative darkness. If you went "+
	    "toward it, your eyes might adjust and be able to see "+
	    "more clearly.\n");

   add_item(({"gloom", "passages", "tunnels"}),
	    "The passages are dark, but there is enough light to "+
	    "see in your immediate area.\n");

   add_exit(THIS_DIR + "topit", "northwest");
   add_exit(THIS_DIR + "2guardrm", "east");
   add_exit(THIS_DIR + "main11", "south");
   add_prop(ROOM_I_INSIDE, 1);
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   if(!living(ob))
      return;
   if(file_name(from) != CAVERNS_DIR+"topit")
      return;
   ob->catch_msg("Your eyes adjust to the lower lighting.\n");
   return;
}
