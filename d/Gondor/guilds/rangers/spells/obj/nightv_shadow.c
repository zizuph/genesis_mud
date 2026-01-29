/*
 *  /d/Gondor/guilds/rangers/spells/obj/nightv_shadow.c
 *
 *  Originally coded by ??
 *
 *  Modification log:
 *    Alto, February 2002. Move, moved spell enhance from Gondor
 *          company to North company.
 *    Gwyneth, October 2003. Added query_ranger_nightvision
 *    Cotillion, March 2021. Fixed incorrect prop management
 */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../rangers.h"

inherit SPELL_OBJECT;
inherit "/std/shadow.c";

int strength,  
    current_see = 0;

void
update_effect(object dest)
{
    shadow_who->inc_prop(LIVE_I_SEE_DARK, -current_see);
    current_see = 0;

    if (!dest->query_prop(ROOM_I_INSIDE))
        current_see = strength;
    else if (shadow_who->query_company() == "north")
        current_see = MAX(1, strength / 2);

    shadow_who->inc_prop(LIVE_I_SEE_DARK, current_see);
}

void
enter_env(object dest, object old)
{
    shadow_who->enter_env(dest, old);
    update_effect(dest);
}

int
query_ranger_nightvision()
{
    return 1;
}

public int
setup_spell_effect()
{
    set_spell_effect_desc("nightvision");

    if (!::setup_spell_effect())
        return 0;


    if (shadow_me(spell_target) != 1)
    {
        spell_target->catch_tell("Nightvision failed, please leave " +
            "bug report about this.\n");
        remove_spell_effect_object();
        return 0;
    }

    strength = max(1, spell_power / 10);
    set_alarm(itof(spell_power * 15), 0.0, dispel_spell_effect);
    log_file("nightvision", "Spell power is: " + spell_power + ", " +
        " Strength is: " + strength + ".\n");
    spell_target->catch_tell("Your eyes feel strange and more perceptive.\n");
    tell_room(ENV(spell_target), QCTNAME(spell_target) + " exclaims " +
      "'Elbereth!', and " + POSSESSIVE(spell_target) + " eyes start " +
      "glowing a faint emerald-green.\n", spell_target);
    spell_target->add_subloc(query_spell_effect_desc(), this_object());
    update_effect(environment(spell_target));
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("Your nightvision slowly fades away.\n");
    tell_room(ENV(spell_target), QCTPNAME(spell_target) + " eyes slowly " +
      "stop glowing.\n", spell_target);

    shadow_who->inc_prop(LIVE_I_SEE_DARK, -current_see);
    current_see = 0;

    spell_target->remove_subloc(query_spell_effect_desc());
    remove_spell_effect_object();
    return 1;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == "eyes" && for_obj != on)
        return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != query_spell_effect_desc())
        return shadow_who->show_subloc(subloc, on, for_obj);

    if (for_obj != on)
    {
        return capitalize(POSSESSIVE(on)) +" eyes sparkle with " +
            "a strange emerald-green glow.\n";
    }
}
