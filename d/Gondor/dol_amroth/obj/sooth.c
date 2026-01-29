/* -*- Mode: C -*-
 *
 * sooth.c
 *
 * Skippern 20(c)02
 *
 * The poison effect of sooth
 */
inherit "/std/poison_effect";

#include <poison_types.h>

create_poison_effect()
{
    set_interval(15);
    set_time(350);
    set_damage( ({ POISON_FATIGUE, 50 }) );
    set_strength(10);
    set_poison_type("sooth");
}
