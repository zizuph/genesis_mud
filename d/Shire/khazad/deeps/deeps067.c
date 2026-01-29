
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 2;
  extraline = "The tunnel bends here heading off to the west and "+
              "southeast.\n";



  WEST(DEEPS_DIR + "deeps065");
  SOUTHEAST(DEEPS_DIR + "deeps069");


  make_the_room();
}
