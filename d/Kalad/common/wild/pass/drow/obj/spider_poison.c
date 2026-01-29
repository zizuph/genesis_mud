inherit "/std/poison_effect";
#include <poison_types.h>

create_poison_effect()
{
   set_interval(10);
   set_time(1000);
   set_damage( ({ POISON_FATIGUE, 100, POISON_HP, 30 }) );
   set_strenght(60);
   set_poison_type("spider");
}
