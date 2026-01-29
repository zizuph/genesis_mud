#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("shirt");
    set_pname("shirts");
    set_adj("brown");
    set_short("brown shirt");
    set_pshort("brown shirts");

    set_long("A brown shirt, not much more than that.\n");
 
    set_layers(15);
    set_looseness(10);
    set_slots(A_TORSO);

    add_prop(OBJ_I_WEIGHT, 500 + random(50));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);   
    add_prop(OBJ_I_VALUE, 5);
}
