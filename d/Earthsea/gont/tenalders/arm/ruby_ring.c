#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("ring");
    set_adj("ruby");
    set_short("ruby ring");
    set_long("A large ruby sits in a "+
        "beautiful setting on this golden ring.\n");
    set_layers(5);
    set_looseness(7);
    set_slots(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT, 50 + random(50));
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 200);
}
