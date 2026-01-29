inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to the northwest and "+
              "south.\n";

  NORTHWEST(DEEPS_DIR + "deeps066");
  SOUTH(DEEPS_DIR + "deeps062");
  make_the_room();
}
