/*
   Poison from the darts, from the evil cleric in the camp at
   Crystalmir lake. Copy of doorpoison.c by Aridor, 08/29/94.
   with lowered poison effects by Jeremiah, 06/19/95.
*/

inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>

void
create_poison_effect()
{
    set_interval(25);
    set_time(500);
    set_damage(({ POISON_FATIGUE, (10 + random(40)), POISON_HP, 100, POISON_STAT, SS_DEX }));
    set_strength(60);
}
