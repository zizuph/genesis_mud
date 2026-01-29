/*
 * /d/Gondor/morgul/obj/corpse_poison.c
 *
 * Cloned from /d/Gondor/morgul/obj/cocoon.c
 * when someone searches the cocoon.
 *
 * Olorin, 30-oct-1993
 */
inherit "/std/poison_effect";

#include <poison_types.h>

create_poison_effect()
{
    ::create_poison_effect();
    set_interval(20);
    set_time(300);
    set_damage(({POISON_MANA, 50, POISON_FATIGUE, 40, POISON_HP, 25}));
    set_strength(25);
    set_poison_type("corpse");
}
