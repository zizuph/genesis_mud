inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 8;
  extraline = "The tunnel runs straight and level off to the northeast "+
              "and southwest.\n";

  NORTHEAST(DEEPS_DIR + "deeps027");
  SOUTHWEST(DEEPS_DIR + "deeps025");
  make_the_room();
}
