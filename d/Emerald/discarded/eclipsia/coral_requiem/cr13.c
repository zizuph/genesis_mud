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
   set_long("    The spring seems to have had an effect on the water " +
      "temperature for the entire cave. The water is considerably " +
      "warmer toward the back of the cave. Another large crack in the " +
      "wall here seems to be a similar spring of sorts. The springs in " +
      "this tunnel probably serve to keep all of the waters in the lake " +
      "at a constant temperature. The cave turns to the southeast here, " +
      "and also leads back to the pavillion southwest.\n\n");
   
   add_item(({"crack", "spring", "fissure", "springs"}), "Hot water " +
      "bursts from the large crack in the wall.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr14", "southeast");
   add_exit(CRDIR + "cr12", "southwest");
}

