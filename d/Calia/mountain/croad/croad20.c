 /* Maniac 9/3/95 */
 /* Slip code by Overlord */
 /* Modified, Maniac 19/9/95 */

inherit "/d/Calia/std/std_croad_mountain";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("The road leads upwards to the southeast " +
      "and down to the west.\n", 21);
    add_exit(CROAD+"croad21","southeast","@@slip", 2);
    add_exit(CROAD+"croad19","west", "@@slip");
}

