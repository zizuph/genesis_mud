#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("breastplate");
    set_pname("breastplates");
    set_adj(({"embossed", "bronze"}));
    set_short("embossed bronze breastplate");
    set_pshort("embossed bronze breastplates");
    set_long("The " +query_short()+ " is molded precisely to fit its original " +
        "owners feminine form. Extravagant embossed patterns " +
        "swirl in various directions about the torso and chest area. " +
        "The armour looks very strong and surprisingly light.\n");
    set_default_armour(40, A_TORSO, ({-1, -1, -1}));
    add_prop(OBJ_I_VALUE, 1100);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 550);
}
