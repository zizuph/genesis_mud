inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to the north "+
              "and southwest.\n";

  NORTH(DEEPS_DIR + "deeps001");
  SOUTHWEST(DEEPS_DIR + "deeps009");
  make_the_room();
}
