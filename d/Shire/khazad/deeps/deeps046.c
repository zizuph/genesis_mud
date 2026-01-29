inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the north, south "+
              "and east.\n";

  NORTH(DEEPS_DIR + "deeps045");
  SOUTH(DEEPS_DIR + "deeps047");
  EAST(DEEPS_DIR + "deeps050");
  make_the_room();
}
