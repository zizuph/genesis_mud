/*
 * /d/Gondor/common/poison/weak_snake_poison.c
 *
 * Cloned from /d/Gondor/common/npc/snake.c
 * in combat (special attack)
 *
 * Olorin, 08-jan-1995
 */
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(60);
    set_time(300 + random(240));
    set_damage(({POISON_STAT, SS_STR, POISON_FATIGUE, 15, POISON_HP, 5}));
    set_strength(30);
    set_poison_type("snake");
}
