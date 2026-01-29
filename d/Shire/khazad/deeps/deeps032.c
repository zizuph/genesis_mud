inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to the east and south.\n";

  EAST(DEEPS_DIR + "deeps033");
  SOUTH(DEEPS_DIR + "deeps031");
  make_the_room();
}
