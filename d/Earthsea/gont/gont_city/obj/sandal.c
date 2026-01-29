#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("sandal");
    set_adj(({"small", "leather"}));
    add_adj("right");
    set_short("small leather sandal");
    set_long("This is a small leather sandal for a "+
        "right foot.\n");
    set_layers(100);
    set_looseness(10);
    set_wf(this_object());
    set_slots(A_R_FOOT);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 5);
}

public int
query_theras_sandal()
{
    return 1;
}
