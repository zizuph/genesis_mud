inherit "/std/poison_effect";
#include <poison_types.h>

void create_poison_effect()
{
  ::create_poison_effect();
  set_interval(25);
  set_time(9000);
  set_damage(({POISON_MANA,75,POISON_FATIGUE,75,POISON_HP,75}));
  set_strength(70);
  set_poison_type("black_touch");
}

