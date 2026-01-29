inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
    set_name("little sign");
    add_name("sign");
    set_adj("little");
    add_name("Gnomish_Incomsign");
    set_pname("little signs");
    set_short("little sign");
    set_long("A board nailed to a wooden stick. It might be a sign "
	     + "or, on a second thought, might be not.\n");
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 10);
}

