
inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


void
create_object()
{
    set_name("feather");
    add_name("_worship_feather_id_");
    set_adj("white");
    set_long("This white feather seems to have fallen " +
      "off a pigeon.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME,20);
}
