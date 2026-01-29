/* Centaur sculpture to go on mount Kyrus.
   Coded by Maniac, 14.9.95
   Updated by Maniac, 16/9/01
*/

inherit "/std/object";
#include <stdproperties.h>
#include "obj.h"


void
create_object()
{
     set_name("statue");
     add_name("centaur");
     set_adj("winged");
     set_short("statue of a winged centaur");
     set_long("A statue of a powerful winged centaur in mid gallop, with " +
              "a great sword held aloft in both hands. The statue faces " +
              "downhill, its eyes appearing to watch the road " +
              "carefully.\n");
     add_prop(OBJ_I_WEIGHT, 1000000);
     add_prop(OBJ_I_VOLUME, 1000000);
     add_prop(OBJ_M_NO_GET, "The statue is much too heavy.\n");
}
