inherit "/std/poison_effect";
#include <poison_types.h>

create_poison_effect()
{
    set_interval(20);
    set_time(2400);
    set_damage( ({POISON_FATIGUE, 300, POISON_HP, 10}) );
    set_strength(20);
    set_poison_type("poison needle");
}
