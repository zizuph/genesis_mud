inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to the "+
              "northeast and west.\n";

  NORTHEAST(DEEPS_DIR + "deeps004");
  WEST(DEEPS_DIR + "deeps016");
  make_the_room();
}
