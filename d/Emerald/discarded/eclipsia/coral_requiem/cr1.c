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
   set_long("    Just to the north, there is an opening which leads " +
      "into a larger room. Occasionally, one of the merfolk will " +
      "walk out with a few items in their possession. This must " +
      "be the store just ahead. The water carries sound very well; " +
      "you can still hear the mermaids singing. The cave continues " +
      "to the southeast.\n\n");
   
   add_item("opening", "The opening leads into the store.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr2", "southeast");
   add_exit(CRDIR + "shop", "north");
}

