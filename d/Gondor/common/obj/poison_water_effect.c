inherit "/std/poison_effect";
#include <poison_types.h>

create_poison_effect()
{
  ::create_poison_effect();
  set_interval(15);
  set_time(900);
  set_damage(({POISON_FATIGUE, 75, POISON_MANA, 100, POISON_HP, 250}));
  set_strength(50);
  set_poison_type("poisoned water");
}

