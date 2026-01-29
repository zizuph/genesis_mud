
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 8;
  extraline = "The tunnel runs straight and level here off to the "+
              "northwest and southeast.\n";



  NORTHWEST(DEEPS_DIR + "deeps067");
  SOUTHEAST(DEEPS_DIR + "deeps070");


  make_the_room();
}
