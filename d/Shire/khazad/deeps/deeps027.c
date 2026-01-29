inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently slopes downhill to the northeast and "+
              "uphill towards the southwest.\n";   

  NORTHEAST(DEEPS_DIR + "deeps028");
  SOUTHWEST(DEEPS_DIR + "deeps026");
  make_the_room();
}
