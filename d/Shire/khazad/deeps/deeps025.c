inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 8;
  extraline = "The tunnel runs straight and level off to the northeast "+
              "and south around a bend.\n";

  NORTHEAST(DEEPS_DIR + "deeps026");
  SOUTH(DEEPS_DIR + "deeps024");
  make_the_room();
}
