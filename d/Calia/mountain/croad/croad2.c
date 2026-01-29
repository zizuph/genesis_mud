 /* Maniac 9/3/95, modified 19/9/95 */
 /* Cr-road code by Overlord */

inherit "/d/Calia/std/std_croad_mountain";
#include <macros.h>
#include "crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("The road leads upwards to the east " +
      "and down to the west.\n", 3);
    add_exit(CROAD+"croad3","east","@@slip", 2);
    add_exit(CROAD+"croad1","west", "@@slip");
}

