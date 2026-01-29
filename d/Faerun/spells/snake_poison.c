/*
 * A snake poison for the drow spell viperhand.
 *
 * Midnight Feb 2004
 */
#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>
#include "/d/Faerun/defs.h"

void
create_poison_effect()
{
    set_interval(20);
    set_time(300);
    set_damage( ({ POISON_FATIGUE, 60, POISON_HP, 60 }) );
    set_strength(60);
    set_poison_type("snake");
}
