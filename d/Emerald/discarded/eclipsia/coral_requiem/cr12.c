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
   set_long("    This cave is noticeably warmer than the other " +
      "waters. You quickly discover why when you feel a current " +
      "coming out of the floor. Looking down, you see a large " +
      "fissure, out of which is flowing a spring of hot water. " +
      "The higher temperatures seem to have an effect on the colour " +
      "of the coral. The colours are of a much redder hue here. " +
      "The cave continues to the northeast and southwest.\n\n");
   
   add_item(({"fissure", "crack", "spring"}), "Hot water flows steadily "+
      "from the large crack in the floor. It is very soothing.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr13", "northeast");
   add_exit(CRDIR + "cr11", "southwest");
}

