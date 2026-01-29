/*
 *  The house of the Hobbiton alchemist
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

create_room() 
{
    add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Alchemist's house");
   set_long(
      "This little cabin is the home of the town alchemist. The alchemist "
    + "is an old and wise hobbit, who knows a lot about magic and magic "
    + "items. On the walls are many weird items, such as a shrine, "
    + "a mortar, a picture of a big dragon and a magical round square.\n");

   add_item("shrine", 
      "The shrine has been carved out of the wall, and it looks like "
    + "it has been filled with some kind of statue, which seems to be "
    + "missing.\n");

   add_item("mortar", 
      "The mortar could be used, together with a pestle, to mash herbs "
    + "and spices to powder. It can also very well be used to mix magical "
    + "items in.\n");

   add_item(({"picture","dragon","big dragon"}), 
      "The picture shows the hideous dragon, called Smaug. It has a foul "
    + "look in its eyes. Everyone knows that the scale of a dragon is a "
    + "powerful magical component, but that is also very rare, and hard "
    + "to get. Many brave warriors have died trying to obtain a "
    + "dragonscale from a dragon.\n");

   add_item(({"square","round square"}), 
      "This object shows the power of the alchemist. You never would have "
    + "believed it, if you didn't see this with your own eyes. Rumour "
    + "has it, that the alchemist is now working on a spheric cube...\n");

   add_exit(STAND_DIR + "bw_road5", "south", 0);

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   reset_room();
}

reset_room() {
   if (!present("alchemist",this_object()))
      clone_object(STAND_DIR + "alchemist")->move(this_object());
}