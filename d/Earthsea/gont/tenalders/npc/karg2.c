#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/npc/basic_karg";

#include <stdproperties.h>

public void
create_karg()
{
    set_living_name("_mr_karg_2_");
    set_levels(1);
    add_equipment(({
        ({ "/d/Earthsea/gont/tenalders/wep/bronze_axe",
        "/d/Earthsea/gont/tenalders/wep/lance" })[random(2)],
        "/d/Earthsea/gont/tenalders/arm/leather_helm",
        "/d/Earthsea/gont/tenalders/arm/ringmail",
        "/d/Earthsea/gont/tenalders/arm/arm_bands" }));
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, random(5), 0}));
}
