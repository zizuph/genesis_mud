inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 6;
  extraline = "The narrow ledge runs off to the northwest and "+
              "southeast.\n";

  NORTHWEST(DEEPS_DIR + "deeps031");
  SOUTHEAST(DEEPS_DIR + "deeps029");
  make_the_room();
}
