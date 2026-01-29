#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/gont/gont_city/liv/basic_sailor";

#include <money.h>
#include "basic_sailor.h"

public void
create_earthsea_monster()
{
    ::create_sailor();
    set_living_name("_seaman3_");
    set_levels(3);
    add_equipment(({ CUTLASS, JERKIN, BREECHES, CAP }));
    add_act("tip cap");
    (MONEY_MAKE_SC(random(20)))->move(this_object());
}
