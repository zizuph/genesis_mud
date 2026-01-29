
inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


void
create_object()
{
    set_name("rock");
    set_adj("small");
    add_adj("grey");
    set_long("This small grey rock is rather rough and weathered, having " +
      "been worn down by the harsh elements common to the " +
      "plains of Estwilde.\n");

    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 1);
}
