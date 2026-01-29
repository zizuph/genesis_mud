inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the west, south "+
              "and east.\n";

  WEST(DEEPS_DIR + "deeps046");
  SOUTH(DEEPS_DIR + "deeps051");
  EAST(DEEPS_DIR + "deeps052");
  make_the_room();
}
