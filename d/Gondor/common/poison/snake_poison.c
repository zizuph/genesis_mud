/*
 * /d/Gondor/common/poison/snake_poison.c
 *
 * Cloned from /d/Gondor/common/npc/snake.c
 * in combat (special attack)
 *
 * Olorin, 21-nov-1994
 */
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(20);
    set_time(240 + random(120));
    set_damage(({POISON_STAT, SS_DEX, POISON_FATIGUE, 15, POISON_HP, 25}));
    set_strength(70);
    set_poison_type("snake");
}
