#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("sash");
    set_adj(({"fringed", "red", "silk" }));
    set_short("red silk sash");
    set_long("A fringed red silk sash that is worn "+
        "about the waist.\n");
    set_layers(11);
    set_looseness(5);
    set_slots(A_WAIST);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 500);
}
