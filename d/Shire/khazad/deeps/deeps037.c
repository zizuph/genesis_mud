inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently slopes downhill to the south and "+
              "uphill towards the west.\n";   

  SOUTH(DEEPS_DIR + "deeps038");
  WEST(DEEPS_DIR + "deeps036");
  make_the_room();
}
