inherit "/std/poison_effect";
#include "/sys/poison_types.h"

create_poison_effect()
{
  ::create_poison_effect();

  set_short("mortia poison");
  set_long("This is the poison caused by the mortia "+
           "flower.\n");

  set_interval(25);
  set_time(1000);
  set_poison_type("herb");
  set_strength(100);

  set_damage(({POISON_HP,50,POISON_FATIGUE,10}));

}
