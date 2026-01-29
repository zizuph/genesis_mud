
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 3;
  extraline = "The tunnel bends here heading off to the "+
              "northwest and east.\n";



  NORTHWEST(DEEPS_DIR + "deeps077");
  EAST(DEEPS_DIR + "deeps075");


  make_the_room();
}
