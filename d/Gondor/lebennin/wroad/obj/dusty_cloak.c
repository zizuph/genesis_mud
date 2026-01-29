#pragma strict_types

inherit "/std/armour.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("grey");
    add_adj(({"dusty", "linen"}));
    set_short("travelworn cloak");
    set_pshort("travelworn cloaks");
    set_long("This cloak bears signs of extensive travels and the seams are " +
        "becoming undone in places. The grey linen seems to be of good " +
        "quality though, and it looks like it will last for years still.\n");

    add_item(({"linen", "cloth", "grey linen"}), "The linen seems to be " +
        "woven by a skilled craftsman, and looks very comfortable.\n");

    set_at(A_ROBE);
    set_ac(2);
    set_am(({ 0, 0, 0}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2, A_ROBE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(2, A_ROBE));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2)); 

}
