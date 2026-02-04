/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "std/room";
#include <stdproperties.h>
#include "defs.h"

#define PATH "/d/Terel/mecien/valley/guild/crypt/"

create_room(){
   
   set_short("Catacomb");
   set_long("A dark and vaulted hall, a catacomb within the crypts. Arched\n" +
      "passages lead off in all directions. The air is cool, the smell of\n" +
      "death is everywhere. Small black diamond shapes are inlaid into the\n" +
      "ceiling, the floor is smooth and polished, the walls bare.\n"
   );
   add_item("walls", "Smooth gray and white stone.\n");
   add_item("floor", "The floor is a smooth gray stone, set with a pattern\n"
            +"of black swirling karmic designs.\n");
   add_item("dust", "From all the ages this dust has collected.\n");
   add_item(({"designs","karmic designs","patterns"}),
           "They look arcane, but seem to serve no purpose.\n");
   
   add_exit(PATH + "crypt2", "east", 0);
   add_exit(MAZE, "north", 0);
   add_exit(PATH + "maus1", "south", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   
}

