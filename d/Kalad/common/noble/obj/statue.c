inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_object()
{
    set_name("statue");
    set_adj("stone");
    set_short("stone statue");
    set_long("This is a statue of a giant eagle. It has its wings spread "+
    "apart and its beak open in a silent scream. In its claws it clutches "+
    "a fish.\n");
    add_prop(OBJ_M_NO_GET,"It is quite heavy and firm in the ground.\n");
}


 
