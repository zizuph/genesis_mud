#pragma save_binary

inherit "/std/poison_effect";
#include <poison_types.h>
#include <ss_types.h>

create_poison_effect()
{
  ::create_poison_effect();
  set_interval(10 + this_player()->query_stat(SS_OCCUP)/10);
  set_time(360 + random(360));
  set_damage(({POISON_STAT, 1, POISON_FATIGUE, 50, POISON_MANA, 150, POISON_HP, 20}));
  set_strength(30);
  set_poison_type("garlic");
}
