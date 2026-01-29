#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("ring");
    set_pname("rings");
    set_adj(({"black diamond", "black", "diamond" }));
    set_short("mysterious black diamond ring");
    set_pshort("mysterious black diamond rings");
    add_adj("mysterious");
    set_long("A large black diamond sits in a "+
        "beautiful setting shaped like a dragon claw, fashioned in "+
        "gold.\n");
    set_layers(5);
    set_looseness(10);
    set_slots(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);   
    add_prop(OBJ_I_VALUE, 2000);
}
