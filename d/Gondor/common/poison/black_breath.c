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
* masked cure_poison
* Olorin, 8-nov-1993
* interval 40 -> 30
* strength 90 -> 100
* POISON_TYPES 150 -> 200
* Elessar, 29-jul-95
* strength 100 -> 120
* The nazgul is not someone to mess with lightly!
* Keeping the nazgul up with the Jonses. A worthy opponent for any
* and all, with a good chance of death for his opponents
* Dunstable, March 20, 1994
*/
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

void 
create_poison_effect()
{
   ::create_poison_effect();
   set_interval(20);
   set_time(9000);
   set_damage(({ POISON_HP,      250, POISON_MANA, 100, 
                 POISON_FATIGUE, 100, POISON_STAT, SS_CON, }));
   set_strength(100);
   set_poison_type("black_breath");
   add_prop(OBJ_M_NO_DROP,"");
}

