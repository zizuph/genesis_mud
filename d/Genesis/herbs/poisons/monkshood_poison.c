#pragma save_binary

inherit "/std/poison_effect";
#include "/sys/poison_types.h"

create_poison_effect()
{
    ::create_poison_effect();

    set_name("_monkshood_poison");
    set_interval(45);
    set_time(400);
    set_poison_type("herb");
    set_strength(120);
    set_damage(({POISON_HP, 75, POISON_FATIGUE, 100}));


}
