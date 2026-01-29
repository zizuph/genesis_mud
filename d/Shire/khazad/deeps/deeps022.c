inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the north, "+
              "west, and southeast.\n";

  NORTH(DEEPS_DIR + "deeps023");
  WEST(DEEPS_DIR + "deeps039");
  SOUTHEAST(DEEPS_DIR + "deeps021");
  make_the_room();
}
