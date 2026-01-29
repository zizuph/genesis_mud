
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
  extraline = "The tunnel bends here heading off to the "+
              "northeast and southeast.\n";



  NORTHEAST(DEEPS_DIR + "deeps078");
  SOUTHEAST(DEEPS_DIR + "deeps076");


  make_the_room();
}
