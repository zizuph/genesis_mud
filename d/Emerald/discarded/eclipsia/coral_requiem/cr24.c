/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

create_room()
{
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    This coral cave has quite a bit of traffic coming " +
      "and going. Fish, merpeople, and various other aquatic " +
      "creatures swim by in both directions. The seaweed is " +
      "constantly swaying as travellers brush past the " +
      "walls en route to their destination. There is life all around " +
      "you.\n\n");
   
   add_item(({"fish", "merpeople", "creatures", "life"}), "Sea " +
      "dwellers of all shapes and sizes are moving lazily " +
      "through the cave.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr21", "east");
   add_exit(CRDIR + "cr25", "north");
}

