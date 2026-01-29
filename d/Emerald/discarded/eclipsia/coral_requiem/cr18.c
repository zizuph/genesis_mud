/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

create_room()
{
   ::create_room();
   clone_object("/d/Emerald/eclipsia/obj/door")->move(this_object());
   set_short("Caves around Coral Requiem");
   set_long("    The cave begins to turn here to the southeast. " +
      "A huge stone door is just ahead. The coral shines brightly " +
      "here, its colourful radiance interrupted by only the smallest " +
      "of cracks in the wall. Other than the seaweed which grows " +
      "here, the cave is quite barren and deserted. The stone doors " +
      "are to the southeast, and the cave also heads back to the " +
      "northeast.\n\n");
   
   remove_item("crack");
   remove_item("cracks");
   add_item(({"cracks", "crack"}), "Tiny cracks snake across the wall. " +
      "One crack in particular looks strange, almost unnatural.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr17", "northeast");
   add_exit(CRDIR + "cr19", "southeast");
}

