#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("pants");
    set_pname("pairs of pants");
    set_adj("old");
    set_adj("dirty");
    set_short("pair of dirty old pants");
    set_pshort("pairs of dirty old pants");

    set_long("A pair of dirty old pants. It is very well worn and beat up, " +
        "but still very sturdy and useful.\n");
 
    set_layers(100);
    set_looseness(10);
    set_slots(A_LEGS);    

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 5);
}
