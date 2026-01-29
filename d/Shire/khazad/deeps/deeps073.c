
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 0;
  extraline = "The tunnel bends here heading off to the northeast "+
              "and west.\n";



  NORTHEAST(DEEPS_DIR + "deeps072");
  WEST(DEEPS_DIR + "deeps074");


  make_the_room();
}
