inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 3;
  extraline = "The narrow tunnel heads off to the northwest and east.\n";

  NORTHWEST(DEEPS_DIR + "deeps030");
  EAST(DEEPS_DIR + "deeps024");
  make_the_room();
}
