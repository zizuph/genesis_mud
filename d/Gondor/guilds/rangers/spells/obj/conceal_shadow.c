/*
 * /d/Gondor/guilds/rangers/spells/obj/conceal_shadow.c
 *
 * The shadow that gets loaded onto an armour for the conceal spell.
 *
 * Coded by Gwyneth, October 2003
 */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../rangers.h"

inherit SPELL_OBJECT;
inherit "/std/shadow";

static int     strength;

public int
setup_spell_effect()
{
    set_spell_effect_desc("conceal");

    if (!::setup_spell_effect())
        return 0;


    if (shadow_me(spell_target) != 1)
    {
        spell_target->catch_tell("Conceal failed, please leave a " +
            "bug report about this.\n");
        remove_spell_effect_object();
        return 0;
    }

    strength = max(1, spell_power/20);
    set_alarm(itof(spell_power * 15), 0.0, dispel_spell_effect);
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    object who = environment(spell_target);

    while (objectp(environment(who)) && !living(who))
        who = environment(who);

    if (!living(who))
        tell_room(who, "The " + spell_target->short() + " shimmers " +
            "briefly.\n");
    else
        who->catch_tell("The " + spell_target->short() + " shimmers " +
            "briefly as the conceal wears off.\n");
    remove_spell_effect_object();
    return 1;
}

