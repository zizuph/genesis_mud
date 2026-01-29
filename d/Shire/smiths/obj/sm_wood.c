inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"

void
create_object()
{
    set_name(({"wood", "pole", "wooden pole","sm_wood"}));
    set_adj(({"piece","piece of","long","rounded"}));
    set_short("wooden pole");
    set_long("This long, rounded piece of wood is useful for "+
        "making handles or hafts if you shape it "+
        "properly.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, 50);
}
