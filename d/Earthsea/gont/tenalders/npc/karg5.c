#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/npc/basic_karg";

#include <money.h>

public void
create_karg()
{
    set_living_name("_mr_karg_5_");
    set_levels(4);
    add_equipment(({
        ({ "/d/Earthsea/gont/tenalders/wep/bronze_axe",
        "/d/Earthsea/gont/tenalders/wep/scimitar" })[random(2)],
        "/d/Earthsea/gont/tenalders/arm/bronze_plate_helm",
        "/d/Earthsea/gont/tenalders/arm/arm_bands",
        "/d/Earthsea/gont/tenalders/arm/bronze_plate" }));
    (MONEY_MAKE_GC(random(10)))->move(this_object(), 1);
}
