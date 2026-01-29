/* -*- Mode: C -*-
 *
 * hangover.c
 *
 * Skippern 20(c)02
 *
 * The poison effect of your hangover from the wine quest.
 */
inherit "/std/poison_effect";

#include <poison_types.h>

create_poison_effect()
{
    set_interval(35);
    set_time(1200);
    set_damage( ({ POISON_FATIGUE, 75, POISON_MANA, 100 }) );
    set_strength(15);
    set_poison_type("hangover");
}
