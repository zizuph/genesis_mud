inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  deep = 1;
  roomtype = 0;
  extraline = "The tunnel continues off to the north and south.\n";

  NORTH(DEEPS_DIR + "deeps003");
  SOUTH(DEEPS_DIR + "deeps001");
  make_the_room();
}
