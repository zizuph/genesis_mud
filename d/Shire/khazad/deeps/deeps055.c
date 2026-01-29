inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to the northwest and "+
              "east.\n";

  NORTHWEST(DEEPS_DIR + "deeps053");
  EAST(DEEPS_DIR + "deeps057");
  make_the_room();
}
