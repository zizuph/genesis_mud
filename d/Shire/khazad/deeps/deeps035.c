inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 0;
  extraline = "The tunnel runs off to the northwest and southeast.\n"; 

  SOUTHEAST(DEEPS_DIR + "deeps036");
  NORTHWEST(DEEPS_DIR + "deeps034");
  make_the_room();
}
