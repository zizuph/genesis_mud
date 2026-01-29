#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("shirt");
    set_pname("shits");
    set_adj(({"raggedy", "plaid"}));
    set_short("raggedy plaid shirt");
    set_pshort("raggedy plaid shirts");
    set_long("An old plaid cotton shirt with holes in it.\n");
    set_layers(15);
    set_looseness(5);
    set_slots(A_TORSO);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 75);
    add_prop(OBJ_I_VALUE, 5);
}
