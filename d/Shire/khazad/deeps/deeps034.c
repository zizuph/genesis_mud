inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 0;
  extraline = "The tunnel runs off to the southeast and west.\n"; 

  SOUTHEAST(DEEPS_DIR + "deeps035");
  WEST(DEEPS_DIR + "deeps033");
  make_the_room();
}
