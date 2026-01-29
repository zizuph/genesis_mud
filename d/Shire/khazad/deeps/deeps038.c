inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends here heading downhill towards "+
              "the south and uphill to the north.\n";

  NORTH(DEEPS_DIR + "deeps037");
  SOUTH(DEEPS_DIR + "deeps0?");
  make_the_room();
}
