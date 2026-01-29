inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently slopes downwards here to the south "+
              "while rising in the northeast.\n";

  NORTHEAST(DEEPS_DIR + "deeps047");
  SOUTH(DEEPS_DIR + "deeps049");
  make_the_room();
}
