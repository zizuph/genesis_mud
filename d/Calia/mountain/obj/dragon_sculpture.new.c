/* Dragon sculpture to go on mount Kyrus.
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
     add_name("dragon");
     add_adj("fearsome");
     set_short("statue of a fearsome dragon");
     set_long("A statue of a fearsome mighty dragon with its " +
              "jaws open wide, ready to unleash a powerful blast " +
              "of flame. Its eyes glare ominously down the " +
              "crystalline road.\n");
     add_prop(OBJ_I_WEIGHT, 1000000);
     add_prop(OBJ_I_VOLUME, 1000000);
     add_prop(OBJ_M_NO_GET, "The statue is much too heavy.\n");
}
