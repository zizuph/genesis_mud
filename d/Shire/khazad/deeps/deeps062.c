inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 8;
  extraline = "The tunnel runs straight and level here off to the north "+
              "and south.\n";

  NORTH(DEEPS_DIR + "deeps064");
  SOUTH(DEEPS_DIR + "deeps060");
  make_the_room();
}
