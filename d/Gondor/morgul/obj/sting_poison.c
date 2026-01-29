/*
 * /d/Gondor/morgul/obj/sting_poison.c
 *
 * Cloned from /d/Gondor/morgul/npc/centipede.c
 * in combat (special attack)
 *
 * Olorin,  1-nov-1993
 */
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(20);
    set_time(600);
    set_damage(({POISON_STAT, SS_STR, POISON_MANA,250,
                 POISON_FATIGUE, 100, POISON_HP, 40}));
    set_strength(50);
    set_poison_type("centipede");
}
