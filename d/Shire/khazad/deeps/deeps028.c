inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends here heading downhill towards "+
              "the northeast and uphill to the southwest.\n";

  NORTHEAST(DEEPS_DIR + "deeps0?");
  SOUTHWEST(DEEPS_DIR + "deeps027");
  make_the_room();
}
