
/*
* Wyvern poison.
*/
#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>

void
create_poison_effect()
{
    set_interval(10);
    set_time(400);
    set_damage( ({ POISON_FATIGUE, 50, POISON_HP, 50 }) );
    set_strength(25);
    set_poison_type("wyvern");
}
