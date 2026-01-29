inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 6;
  extraline = "The narrow ledge runs off to the north and "+
              "southeast.\n";

  NORTH(DEEPS_DIR + "deeps032");
  SOUTHEAST(DEEPS_DIR + "deeps030");
  make_the_room();
}
