inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends here to the south "+
              "while rising to the north.\n";

  NORTH(DEEPS_DIR + "deeps048");
  SOUTH(DEEPS_DIR + "deeps0?");
  make_the_room();
}
