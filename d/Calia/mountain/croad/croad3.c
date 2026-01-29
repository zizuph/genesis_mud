 /* Maniac 9/3/95,
    Modified 12/5/95, 19/9/95 Maniac */
 /* Slip code by Overlord */

inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("The road leads upwards to the southeast " +
      "and down to the west.\n", 4);
    add_exit(CROAD+"croad4","southeast","@@slip", 2);
    add_exit(CROAD+"croad2","west", "@@slip");

    clone_object(MOUNTAIN_OBJ+"eagle_sculpture")->move(this_object());
}

