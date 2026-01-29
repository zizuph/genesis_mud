inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the north, east "+
              "and southwest.\n";

  NORTH(DEEPS_DIR + "deeps046");
  EAST(DEEPS_DIR + "deeps051");
  SOUTHWEST(DEEPS_DIR + "deeps048");
  make_the_room();
}
