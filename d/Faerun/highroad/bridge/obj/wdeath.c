inherit "/std/poison_effect.c";
#include <poison_types.h>

create_poison_effect() 
{
	set_interval(20);
	set_time(500);
	set_damage(({POISON_HP, 30}));
	set_strength(20);
	set_poison_type("curse");
}
