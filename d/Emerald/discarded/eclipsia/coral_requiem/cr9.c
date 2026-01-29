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
   set_long("    Strange shadows move about the room, caused " +
      "partially caused by your movements, and partially caused by " +
      "what little light the coral still gives off. A great iron " +
      "gate is to the southwest. It has no apparent door on " +
      "it, but the iron bars are far enough apart that you could " +
      "probably slip through...\n\n");
   
   add_item(({"gate", "iron gate", "bars", "iron bars"}),
      "The iron bars on the gate are far enough apart for you to fit " +
      "through most likely.\n");
   add_item("shadows", "Odd shadows caused by the coral and your " +
      "movements play strangely on the cave around you.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr8", "northeast");
   add_exit(CRDIR + "cr10", "southwest");
}

