inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to "+
              "the east and southwest.\n";

  EAST(DEEPS_DIR + "deeps011");
  SOUTHWEST(DEEPS_DIR + "deeps005");
  make_the_room();
}
