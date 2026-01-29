#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("boots");
    add_name("pair of spiked boots");
    set_pname("pairs of spiked boots");
    set_pshort("pairs of spiked boots");
    set_adj(({"spiked", "tough", "leather"}));
    set_short("pair of spiked boots");
    set_long("A pair of tough leather boots "+
        "which have a sharp bronze spike protruding from the big toe. "+
        "The soles and heels are reinforced with bronze plate.\n");
    set_default_armour(25, A_FEET, ({0, 0, -1}));
    add_prop(OBJ_I_WEIGHT,  900);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 400 + random(50));
}
