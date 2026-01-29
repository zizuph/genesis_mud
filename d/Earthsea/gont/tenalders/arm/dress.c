#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("dress");
    set_pname("dresses");
    set_adj(({"brown", "homespun"}));
    set_short("brown homespun dress");
    set_pshort("brown homespun dresses");
    set_long("A long brown dress made of "+
        "some soft homespun woolen material. It is plain yet "+
        "not unattractive.\n");
    set_layers(100);
    set_looseness(10);
    set_slots(A_ROBE);
    add_prop(OBJ_I_WEIGHT, 500 + random(50));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, 5);
}
