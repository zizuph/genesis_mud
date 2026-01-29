 /* Maniac 9/3/95 */
 /* Slip code by Overlord */
 /* Modified, Maniac 19/9/95 */

inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "/d/Calia/mountain/croad/crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("The road leads upwards to the north " +
      "and down to the southeast.\n", 16);
    add_exit(CROAD+"croad16","north","@@slip", 2);
    add_exit(CROAD+"croad14","southeast", "@@slip");

    clone_object(MOUNTAIN_OBJ+"centaur_sculpture")->move(this_object());
}

