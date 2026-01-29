#include "defs.h"
#include <stdproperties.h>

inherit "/std/object";

create_object()
{
    set_name("chair");
    set_pname("chairs");

    set_adj("grey");
    add_adj("wooden");

    set_short("grey wooden chair");
    set_pshort("grey wooden chairs");

    set_long("This is a grey wooden chair belonging to Kybert.\n");

    add_prop(OBJ_I_WEIGHT, 2000); /* grams */
    add_prop(OBJ_I_VOLUME, 40*40*50);
    add_prop(OBJ_I_VALUE, 12);
}
