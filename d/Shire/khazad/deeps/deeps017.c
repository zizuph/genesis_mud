inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently descends here to the east "+
              "while rising to the northwest.\n";

  NORTHWEST(DEEPS_DIR + "deeps009");
  EAST(DEEPS_DIR + "deeps019");
  make_the_room();
}
