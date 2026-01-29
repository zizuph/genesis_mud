inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 0;
  extraline = "The tunnel runs off to the east and west.\n"; 

  EAST(DEEPS_DIR + "deeps034");
  WEST(DEEPS_DIR + "deeps032");
  make_the_room();
}
