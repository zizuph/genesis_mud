/*
 * /d/Gondor/common/poison/weak_bee_sting.c
 * antidote: savory
 *
 * for bees in newbie area: lasts a short time, doesn't lower any stats
 *
 */

#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>		/* for POISON_*		*/

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(60);
    set_time( 70 + random(50));
    set_damage(({POISON_FATIGUE,2,POISON_HP,5}));
    set_strength(10 + random(6));
    set_poison_type("bee");
}
