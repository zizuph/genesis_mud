/* Eagle sculpture to go on mount Kyrus.
   Coded by Maniac, 14.9.95
   Updated by Maniac 16/9/01
*/

inherit "/std/object";
#include <stdproperties.h>
#include "obj.h"

void
create_object()
{
     set_name("statue");
     add_name("eagle");
     set_short("statue of an eagle");
     set_long("A statue of an great eagle in flight, talons ready " +
              "to grab and rend its prey. The eagle's keen eyes " +
              "observe the lower reaches of the mountain.\n");
     add_prop(OBJ_I_WEIGHT, 1000000);
     add_prop(OBJ_I_VOLUME, 1000000);
     add_prop(OBJ_M_NO_GET, "The statue is much too heavy.\n");
}
