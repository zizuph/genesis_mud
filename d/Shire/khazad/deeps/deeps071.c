
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
  extraline = "The tunnel runs off to the northwest and to the "+
              "southwest around a bend.\n";



  NORTHWEST(DEEPS_DIR + "deeps070");
  SOUTHWEST(DEEPS_DIR + "deeps072");


  make_the_room();
}
