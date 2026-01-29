
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 7;
  extraline = "The tunnel splits up here heading off to the "+
              "north, west, and east.\n";



  NORTH(DEEPS_DIR + "deeps?");
  WEST(DEEPS_DIR + "deeps076");
  EAST(DEEPS_DIR + "deeps074");

  make_the_room();
}
