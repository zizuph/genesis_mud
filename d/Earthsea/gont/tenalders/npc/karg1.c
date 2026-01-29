#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/npc/basic_karg";

#include <stdproperties.h>

#define WEAPON ({ \
    "/d/Earthsea/gont/tenalders/wep/lance", \
    "/d/Earthsea/gont/tenalders/wep/club" })

public void
create_karg()
{
    set_living_name("_mr_karg_1_");
    set_levels(0);
    add_equipment(({
        ({ "/d/Earthsea/gont/tenalders/wep/lance",
        "/d/Earthsea/gont/tenalders/wep/club" })[random(2)],
        "/d/Earthsea/gont/tenalders/arm/leather_armour",
        "/d/Earthsea/gont/tenalders/arm/leather_helm" }));
    add_prop(OBJ_M_HAS_MONEY, ({ 0, random(20), 0, 0}));
}
