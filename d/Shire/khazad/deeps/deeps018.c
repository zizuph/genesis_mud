inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends here to the "+
              "northwest and southeast while rising to the "+
              "northeast.\n";

  NORTHWEST(DEEPS_DIR + "deeps054");
  NORTHEAST(DEEPS_DIR + "deeps016");
  SOUTHEAST(DEEPS_DIR + "deeps0?");
  make_the_room();
}
