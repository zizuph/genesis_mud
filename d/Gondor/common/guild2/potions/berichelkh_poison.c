#pragma save_binary

inherit "/std/poison_effect";
#include <poison_types.h>

#include "potion_defs.h"

void
create_poison_effect()
{
    ::create_poison_effect();
    add_name(MORGUL_S_BERICHELKH_POISON_NAME);
    add_name("ringurth_ingr1");
    set_interval(10000);
    set_silent(1);
    set_time(query_strength()*15);
}
