inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the northwest, "+
              "northeast, and south.\n";

  NORTHWEST(DEEPS_DIR + "deeps004");
  NORTHEAST(DEEPS_DIR + "deeps005");
  SOUTH(DEEPS_DIR + "deeps002");
  make_the_room();
}
