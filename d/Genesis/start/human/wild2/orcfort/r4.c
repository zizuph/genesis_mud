#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "local.h"

void
create_room()
{
   set_short("Fortress hallway");
   set_long("To the east stands an archway that leads into some sort\n"
      + "of an establishment. The sounds of laughter and rude noises  \n"
      + "seem to have intensified. You can faintly smell beer or some\n"
      + "other sort of alcohol. There stands another archway to your\n"
      + "north that seems very dark and gloomy.\n");

   add_item(({"archway", "eastern archway"}),
  "You can just make out a bar through the arch.\n");
   add_item(({"dark archway", "gloomy archway"}),
              "It seems very strange.\n");
   add_item(({"stones", "stone"}), "They are all cut the wrong way, "+
              "and are the incorrect size.\n");

   add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");

   add_exit(ORC+"r3", "south");
   add_exit(ORC+"inn2", "east");
   add_exit(ORC+"r5", "north");
}
