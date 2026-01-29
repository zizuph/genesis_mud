/*
 * copied from /d/Gondor/common/poison/black_breath.c to
 *             /d/Gondor/common/guild2/poisons/black_breath.c
 * to be used a poison for the morthul spell of the Morgul Mages
 * Olorin, 15-jul-1994
 */
#pragma strict_types
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void 
create_poison_effect()
{
    ::create_poison_effect();
    set_name("Black breath");
    set_interval(20);
    set_time(1800);
    set_damage(({ POISON_HP, 250, POISON_MANA, 100,
	POISON_FATIGUE, 25, POISON_STAT, SS_CON, }));
    set_strength(100);
    set_poison_type("black_breath");
}

