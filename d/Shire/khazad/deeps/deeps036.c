inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 0;
  extraline = "The tunnel runs off to the northwest and east.\n"; 

  EAST(DEEPS_DIR + "deeps037");
  NORTHWEST(DEEPS_DIR + "deeps035");
  make_the_room();
}
