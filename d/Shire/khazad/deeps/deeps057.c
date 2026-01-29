inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
 
void
create_room()
{
  roomtype = 3;
  extraline = "The tunnel bends here heading off to the west and "+
              "southeast.\n";

  WEST(DEEPS_DIR + "deeps055");
  SOUTHEAST(DEEPS_DIR + "deeps059");
  make_the_room();
}
