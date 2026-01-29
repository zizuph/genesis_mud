#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("circlet");
    set_adj("gold");
    set_short("gold circlet");
    set_long("A circlet of filigree gold, which one can wear on the head.\n");
    set_layers(100);
    set_looseness(10);
    set_slots(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 30);   
    add_prop(OBJ_I_VALUE, 100);
}
