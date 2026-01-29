#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name(({"pants", "pair"}));
    set_pname(({"pants","pair"}));
    set_adj(({"diaphanous", "silky", "white"}));
    set_short("pair of diaphanous white harem pants");
    set_pshort("pairs of diaphanous white harem pants");
    set_long("A pair of diaphanous silky white harem pants.\n");
    set_layers(15);
    set_looseness(10);
    set_slots(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 500 + random(50));
    add_prop(OBJ_I_VOLUME, 55);
    add_prop(OBJ_I_VALUE, 50);
}
