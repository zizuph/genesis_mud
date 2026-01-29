inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently slopes downhill to the north and "+
              "uphill towards the southeast.\n";   

  NORTH(DEEPS_DIR + "deeps021");
  SOUTHEAST(DEEPS_DIR + "deeps013");
  make_the_room();
}
