#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("loincloth");
    set_adj(({"black", "silk"}));
    set_short("black silk loincloth");
    set_pshort("black silk loincloths");
    set_long("A black silk loincloth. It wraps around the "+
        "buttocks, between the legs, and ties like a sash in front. "+
        "A long tassle decorated with gold thread dangles down.\n");
    set_layers(15);
    set_looseness(10);
    set_slots(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 500 + random(50));
    add_prop(OBJ_I_VOLUME, 110);
    add_prop(OBJ_I_VALUE, 100);
}
