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
   set_long("    As you move away from the large open court area, " +
      "the gaiety of the atmosphere quickly fades as you find yourself " +
      "being enclosed in coral walls. Beneath your feet the " +
      "floor has become smoother and more slippery. Fish ignore you " +
      "as they swim all around you. All along the bottom of the coral " +
      "walls, seaweed grows. It sways with the current of the water " +
      "as bubbles of all sizes float around everywhere.\n\n");
   
   add_item("bubbles", "Your movements cause tiny bubbles which " +
      "drift casually to the cave's ceiling.\n");
   add_item("fish", "Multi-coloured fish swim in schools " +
      "all around. They don't seem to notice you.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr24", "west");
   add_exit(CRDIR + "bwl", "southeast");
}

