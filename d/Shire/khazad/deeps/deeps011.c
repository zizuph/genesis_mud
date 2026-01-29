inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently slopes downwards here heading "+
              "to the north and uphill to the west.\n";

  NORTH(DEEPS_DIR + "deeps014");
  WEST(DEEPS_DIR + "deeps008");
  make_the_room();
}
