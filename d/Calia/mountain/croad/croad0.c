 /* Digit 01 FEB 95 */
 /* Modified Maniac 9/3/95, 25/4/95, 19/9/95 */
 /* Cr-road code by Overlord */

inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("The road leads upwards to the east " +
      "and down to the northwest.\n", 1);
    add_exit(CROAD+"croad1","east","@@slip", 2);
    add_exit(ROAD+"road9","northwest");
}

