inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the west and north. "+
              "The tunnel also rises rapidly to the southeast.\n";

  WEST(DEEPS_DIR + "deeps052");
  NORTH(DEEPS_DIR + "deeps056");
  SOUTHEAST(DEEPS_DIR + "deeps018");
  make_the_room();
}
