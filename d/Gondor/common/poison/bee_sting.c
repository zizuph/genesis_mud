/*
 * /d/Gondor/common/poison/bee_sting.c
 * antidote: savory
 *
 *	Modification log:
 *	07-feb-96: changed SS_CON, SS_DIS stat poisoning to
 *	           SS_WIS, SS_STR stat poisoning. SS_CON stat
 *	           poisoning is extremely dangerous as reduced
 *	           CON increases the effectivity of the poison.
 *	           10 bee stings were able to kill a player of
 *	           CON 120.
 *	           Olorin
 */
inherit "/std/poison_effect";
#include <poison_types.h>
#include <ss_types.h>

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(30);
    set_time( 600 + random(300));
    set_damage(({POISON_FATIGUE,2,POISON_HP,5,POISON_STAT,SS_WIS,POISON_STAT,SS_STR}));
    set_strength(20 + random(6));
    set_poison_type("bee");
}

