inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 3;
  extraline = "The tunnel bends here heading off to the northeast and "+
              "south.\n";

  NORTHEAST(DEEPS_DIR + "deeps058");
  SOUTH(DEEPS_DIR + "deeps054");
  make_the_room();
}
