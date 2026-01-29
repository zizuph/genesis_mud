inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently descends downwards here to the "+
              "north and rises to the southeast.\n";

  SOUTHEAST(DEEPS_DIR + "deeps004");
  NORTH(DEEPS_DIR + "deeps013");
  make_the_room();
}
