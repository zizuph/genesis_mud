
/* Created with a template for quick room generation. */
/* Glaurung 2-96                                      */

inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"

void
create_room()
{
  roomtype = 4;
  extraline = "The tunnel gently descends here to the north "+
              "while rising in the southwest.\n";



  NORTH(DEEPS_DIR + "deeps079");
  SOUTHWEST(DEEPS_DIR + "deeps077");


  make_the_room();
}
