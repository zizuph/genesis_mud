/*
 * Poison delivered by lizardman guard of the Brix in
 * the Aesthetics quarter of Palanthas
 *
 * Mortis 05.2006
 *
 */

inherit "/std/poison_effect";

#include <poison_types.h>

create_poison_effect()
{
	set_interval(21);
	set_time(315);
	set_damage(({POISON_FATIGUE, 115}));
	set_strength(33);
	set_poison_type("lizardman");
}
