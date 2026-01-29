inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 8;
  extraline = "The tunnel runs straight and level here off to the west "+
              "and east.\n";

  WEST(DEEPS_DIR + "deeps050");
  EAST(DEEPS_DIR + "deeps054");
  make_the_room();
}
