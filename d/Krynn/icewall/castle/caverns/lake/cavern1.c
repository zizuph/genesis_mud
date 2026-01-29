/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

object eel;

create_icewall_room()
{
   set_short("Centre Of Lake");
   set_long(
      "You find yourself standing waistdeep in a very cold and "
      + "nearly frozen lake. Very high above you is a manhole "
      + "which you realize is unreachable. Strange ripples are forming "
      + "upon the surface of the water. Perhaps you are not alone."
      + "\n");
   
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

   add_item(({"lake","water"}),"The lake water is very cold and nearly "
	+ "frozen.\n");
   add_item("manhole","It is high above you and very unreachable.\n");
   add_item("ripples","Something other than you is causing them.\n");

   add_exit(CAVE + "cavern2.c", "north");
   add_exit(CAVE + "cavern3.c", "northeast");
   add_exit(CAVERNS + "cavern4.c", "east");
   add_exit(CAVE + "cavern5.c", "southeast");
   add_exit(CAVE + "cavern6.c", "south");
   add_exit(CAVE + "cavern7.c", "southwest");
   add_exit(CAVE + "cavern8.c", "west");
   add_exit(CAVE + "cavern9.c", "northwest");
   
   reset_icewall_room();
}

reset_icewall_room()
{
/* perhaps more than just a lame eel here... */
   if(!eel) 
      {
      eel=clone_object(ICE_CAST_M + "eel.c");
      eel->move(TO);
   }
}
