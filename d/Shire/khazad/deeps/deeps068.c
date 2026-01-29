
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 5;
  extraline = "The tunnel rapidly descends here to the west while "+
              "rising in the east.\n";



  WEST(DEEPS_DIR + "deeps?");
  EAST(DEEPS_DIR + "deeps066");


  make_the_room();
}
