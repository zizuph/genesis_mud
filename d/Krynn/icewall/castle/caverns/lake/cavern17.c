/*Created by Stevenson*/

/* put a wooden door here. no lock, just a standard door. */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Stalactites & Stalagmites");
   set_long(
      "You are in a room of beauty. Mineral-rich water dripping from the "
      + "the ceiling has caused many stalagmites and stalactites to form, "
      + "capturing the colors of the rainbow. As their colors reflect off "
      + "the face of the water you are nearly blinded with the brilliance. "
      + "You also notice a constant supply of water coming out of a "
      + "large hole about ten feet above the water. "
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item("ceiling","The ceiling above you is studded with tiny spots of "
      + "brilliance reflecting the room's light in a shimmering array of "
      + "beauty. "
      + "\n");
   add_item("rainbow","It is very colorful.\n");
   add_item("hole","It is unreachable.\n");
   add_item("stalactites","They descend from the ceiling.\n");
   add_item("stalagmites","They stick out from the ground.\n");
   add_item("water","The reflections of the stalagmites and stalactites "
      + "merge into a colorful rainbow in the water.\n");
   
   add_exit(CAVE+"cavern18.c","east");
   add_exit(CAVE+"cavern6.c","north");
}
