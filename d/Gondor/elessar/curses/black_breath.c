/*
 * modifed, 9-jul-1993
 *
 * the HP damage was set to 40, with interval 60 this cannot
 * endanger any player that is a worthy opponent of the nazgul
 *
 * set_interval 45 -> 40
 * POISON_HP 100 -> 150
 * Olorin, 12-sep-1993
 * set_interval 40 -> 30
 * strength     80 -> 90
 * Olorin, 29-oct-1993
 */
inherit "/std/poison_effect";
#include <poison_types.h>

create_poison_effect()
{
  ::create_poison_effect();
  set_interval(40);
  set_time(20000);
  set_damage(({POISON_MANA,150,POISON_FATIGUE,150,POISON_HP,150}));
  set_strength(80);
  set_poison_type("black_breath");
}

