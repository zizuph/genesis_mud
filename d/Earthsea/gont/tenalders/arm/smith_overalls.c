#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("overalls");
    add_name(({"pants"}));
    set_adj(({"worn","leather"}));
    set_short("pair of worn leather overalls");
    set_pshort("pairs of worn leather overalls");
    set_short("pair of worn leather overalls");
    set_long("A pair of worn out leather overalls.\n");
    set_layers(15);
    set_looseness(10);
    set_slots(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 500 + random(50));
    add_prop(OBJ_I_VOLUME, 110);
    add_prop(OBJ_I_VALUE, 5);
}
