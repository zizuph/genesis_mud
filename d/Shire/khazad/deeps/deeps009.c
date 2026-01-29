inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the "+
              "northeast, southeast, and west.\n";

  NORTHEAST(DEEPS_DIR + "deeps006");
  SOUTHEAST(DEEPS_DIR + "deeps017");
  WEST(DEEPS_DIR + "deeps012");
  make_the_room();
}
