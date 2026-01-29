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
    make_the_room("The road leads upwards to the west " +
      "and down to the northeast.\n", 12);
    add_exit(CROAD+"croad12","west","@@slip", 2);
    add_exit(CROAD+"croad10","northeast", "@@slip");

    clone_object(MOUNTAIN_OBJ+"dragon_sculpture")->move(this_object());
}

