/* the poison effect for yellow_snow.c
Created by Stevenson */

#include <poison_types.h>
inherit "/std/poison_effect";

create_poison_effect() {
   set_interval(20);
   set_time(500);
   set_damage(({POISON_FATIGUE, 100, POISON_HP, 30}));
   set_strength(20);
   set_poison_type("yellow snow");
}
