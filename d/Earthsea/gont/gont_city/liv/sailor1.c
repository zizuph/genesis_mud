#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/gont/gont_city/liv/basic_sailor";

#include <money.h>
#include "basic_sailor.h"

public void
create_earthsea_monster()
{
    object to = this_object();
    ::create_sailor();
    set_living_name("_seaman1_");
    set_levels(1);
    set_act_time(90);
    add_act("tip cap");
    add_act("play harmonica");
    add_equipment(({ BREECHES, BANDANA, DAGGER, CAP, HARMONICA }));
    (MONEY_MAKE_SC(random(20)))->move(to);
}
