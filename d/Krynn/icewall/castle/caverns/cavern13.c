/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("A side cavern");
   set_long(BS(
         "You are in a room that is going uphill to the west and "
         + "downhill to the east. You find it difficult to "
         + "maintain your balance in this chilly, arctic room.\n"
         ,70));
   
   add_exit(CAVERNS + "cavern12.c", "west", "@@slip");
   add_exit(CAVE + "cavern14.c", "east");
}

int slip() {
   if (random(2)-1) { write(
         "\nTrudging carefully uphill, you slip on a piece of ice.\n");
      return 1;
   }
   return 0;
}
