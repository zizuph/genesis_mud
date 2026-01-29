/* A girl's doll */
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
void
create_object()
{
    set_name("doll");
    set_adj("girls");
    set_adj("little");
    set_short("little girls doll");
    set_long(
       "It is a doll made of linen and stuffed with fur. It has black "+
       "hair and eyes, and is wearing a white tunic.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 3);
}
