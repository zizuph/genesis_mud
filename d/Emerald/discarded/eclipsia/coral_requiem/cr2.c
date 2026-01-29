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
   set_long("    A myriad of tiny fish swim up and down the tunnel. " +
      "You notice a small seahorse sneak into a crack in the coral. " +
      "Life prospers here. It can be found in almost every corner. " +
      "The climate is agreeable to about everything that lives here. " +
      "You can faintly hear the mermaids singing from back in the " +
      "central court, and you begin to understand why they never lack " +
      "something to sing about. The cave continues to the " +
      "northwest and southeast.\n\n");
   
   add_item("fish", "You never knew there were so many different kinds " +
      "of fish. Hundreds of them swim in all directions.\n");
   add_item("seahorse", "Occasionally, the seahorse will poke his head " +
      "out of the crack he makes his home in.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr1", "northwest");
   add_exit(CRDIR + "cr3", "southeast");
}

