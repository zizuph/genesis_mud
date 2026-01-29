/*
 * /d/Gondor/guilds/rangers/obj/poisons/warg_poison.c
 *
 * Cloned from /d/Gondor/guilds/rangers/npc/white_warg.c
 * in combat (special attack)
 *
 * Borrowed from Olorin's snake poison
 * by Tigerlily--2004-10-10
 */
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_poison_effect()
{
    ::create_poison_effect();
    set_interval(35);
    set_time(240 + random(60));
    set_damage(({POISON_MANA, 150, POISON_HP, 100}));
    set_strength(70);
    set_poison_type("warg");
    add_prop(OBJ_M_NO_DROP, "");
}
