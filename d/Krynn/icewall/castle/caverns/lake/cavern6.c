/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

object eel;

create_icewall_room()
{
   set_short("Lake Center");
   set_long(
      "You are standing near the center of the lake. Ripples upon the "
      + "surface of the water suggest life other than your own. The lake "
      + "itself stretches out both north and south in a semi-rectangular "
      + "shape. Far to the south you see large stalactites and stalagmites "
      + "jutting from both floor and ceiling. "
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item("ripples","I wouldn't stay around long enough to find out "
      + "what is causing them if I were you.\n");
   add_item("lake","The nearly frozen underground lake of Icewall is "
      + "quite a thing of beauty. Perhaps you will live long enough to "
      + "see the entirety of it.\n");
   
   add_exit(CAVE + "cavern1.c", "north");
   add_exit(CAVE+"cavern17.c","south");
}
