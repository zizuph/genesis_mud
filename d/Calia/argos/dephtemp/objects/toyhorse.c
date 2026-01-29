/* A toy winged horse */
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
void
create_object()
{
    set_name(({"toy horse","toy","horse"}));
    set_adj("black");
    set_short("toy horse");
    set_long(
       "It is a winged toy horse made of black linen and stuffed with fur. "+
       "It has red eyes made of buttons and its mane and tail look real.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 3);
}
