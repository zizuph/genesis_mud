inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently slopes downwards here to "+
              "the southwest and uphill to the east.\n";

  EAST(DEEPS_DIR + "deeps009");
  SOUTHWEST(DEEPS_DIR + "deeps015");
  make_the_room();
}
