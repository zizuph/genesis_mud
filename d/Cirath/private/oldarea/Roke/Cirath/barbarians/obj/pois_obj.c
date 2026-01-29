inherit "/std/poison_effect";
#include "/sys/poison_types.h"

create_poison_effect()
{
  ::create_poison_effect();

  set_interval(20);
  set_time(200);
  set_poison_type("cloud");
  set_strength(50);

  set_damage(({POISON_HP,30,POISON_FATIGUE,30}));

}
