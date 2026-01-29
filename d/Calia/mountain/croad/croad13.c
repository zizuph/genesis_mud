 /* Maniac 9/3/95 */
 /* Slip code by Overlord */

inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("The road leads upwards to the northwest " +
      "and down to the east.\n", 14);
    add_exit(CROAD+"croad14","northwest","@@slip", 2);
    add_exit(CROAD+"croad12","east", "@@slip");
}

