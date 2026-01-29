/*
 * Cilenze object
 *
 * Silence an object, making them unable to speak
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#define GAG_MESSAGE  "Your tongue is burning wildly, making you unable to speak!\n"

public int
start()
{

    if (stringp(spell_target->query_prop(LIVE_M_MOUTH_BLOCKED)))
    {
        set_alarm(1.0, 0.0, &dispel_spell_effect());

        return 1;
    }

    spell_target->add_prop(LIVE_M_MOUTH_BLOCKED, GAG_MESSAGE);


    return 1;
}

varargs public int
dispel_spell_effect(object dispeler)
{
    string str;
    object target = environment(shadow_who);

    shadow_who->remove_prop(LIVE_M_MOUTH_BLOCKED);

    target->catch_msg("Your mouth stops burning and returns to normal again.\n");

    remove_spell_effect_object();
    return 1;
}

void
set_spell_duration(int t)
{
    set_alarm(itof(t), 0.0, &dispel_spell_effect());
}
