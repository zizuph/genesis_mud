inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently descends here to the "+
              "southwest while rising to the east.\n";

  EAST(DEEPS_DIR + "deeps010");
  SOUTHWEST(DEEPS_DIR + "deeps018");
  make_the_room();
}
