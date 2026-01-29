inherit "/std/poison_effect";

#include <poison_types.h>

create_poison_effect()
{
    ::create_poison_effect();
    set_interval(10);
    set_time(600);
    set_damage(({POISON_MANA, 50, POISON_FATIGUE, 40, POISON_HP, 200}));
    set_strength(150);
    set_poison_type("spider");
}
