inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends downwards here to "+
              "the northwest and uphill to the south.\n";

  NORTHWEST(DEEPS_DIR + "deeps020");
  SOUTH(DEEPS_DIR + "deeps007");
  make_the_room();
}
