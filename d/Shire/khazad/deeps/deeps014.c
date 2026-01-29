inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends here to "+
              "the north and rises to the south.\n";

  NORTH(DEEPS_DIR + "deeps0?");
  SOUTH(DEEPS_DIR + "deeps011");
  make_the_room();
}
