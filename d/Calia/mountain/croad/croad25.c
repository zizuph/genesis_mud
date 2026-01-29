 /* Maniac 27/3/95 */
 /* Slip code by Overlord */
 /* Modified, Maniac 19/9/95 */

inherit "/d/Calia/std/std_plateau";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

void
create_room()
{
    make_the_room("\n", 2);
    add_exit(CROAD+"croad26","north","@@slip");
    add_exit(CROAD+"croad24","south", "@@slip");
}

