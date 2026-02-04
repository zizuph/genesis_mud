inherit "/std/poison_effect";
#include <poison_types.h>
#include "../bhunters.h"

create_poison_effect()
{
	set_interval(20);
	set_time(1500);
	set_damage( ({ POISON_FATIGUE, 200, POISON_HP, 50 }) );
	set_strength(50);
	set_poison_type("trap");
}

public varargs void start_poison(object poisoner)
{
	FIX_EUID;
	::start_poison(poisoner);
	object poison_shadow = clone_object(BHTRAPS + "poison_shadow");
	poison_shadow->shadow_me(E(TO));
	E(TO)->catch_msg("A weird, definetly not pleasant feelings goes throw your stomach.\n");
}

public void remove_object()
{
	E(TO)->remove_poison_shadow();
	::remove_object();
}