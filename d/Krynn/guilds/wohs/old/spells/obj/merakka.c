/*
 * Merakka object
 *
 * Give an object ability to see invisible object.
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

int gSeeInvis;

public int
start()
{
    gSeeInvis = 1;

    spell_target->add_prop(LIVE_I_SEE_INVIS,
        spell_target->query_prop(LIVE_I_SEE_INVIS) + gSeeInvis);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeler)
{
    object target = environment(shadow_who);

    shadow_who->add_prop(LIVE_I_SEE_INVIS, shadow_who->query_prop(LIVE_I_SEE_INVIS) -
        gSeeInvis);

    if (!shadow_who->query_prop(LIVE_I_SEE_INVIS))
    {
        target->catch_msg("The translucent vision slowly fades, you blink your " +
           "eyes slightly as they return to normal.\n");
        return 1;
    }

    remove_spell_effect_object();
    return 1;
}

void
set_spell_duration(int t)
{
    set_alarm(itof(t), 0.0, &dispel_spell_effect());
}
