/* 
 * phearing - true hearing
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

int gAlarm, gSkill;

varargs public int
dispell_spell_effect(object dispeller)
{
    query_shadow_who()->catch_tell("Suddenly it grows quieter.\n");

    set_alarm(0.0, 0.0, &remove_spell_effect_object());

    return 1;
}

int
query_phearing_object()
{
    return 1;
}

int
query_skill(int snum)
{
    /* Hide it to show the original when the command skills is issued */
    if ((snum == SS_LANGUAGE || snum == SS_AWARENESS) &&
        (calling_program() == "cmd/live/state.c" ||
        query_verb() == "skills"))
        return query_shadow_who()->query_skill(snum);

    switch (snum)
    {
        case SS_AWARENESS:
            return query_shadow_who()->query_skill(SS_AWARENESS) +
                ((gSkill / 3) * 2);
        case SS_LANGUAGE:
            return query_shadow_who()->query_skill(SS_LANGUAGE) +
                gSkill;
        default:
            return query_shadow_who()->query_skill(snum);
    }
}

void
set_time(int t)
{
    gAlarm = set_alarm(itof(t), 0.0, &dispell_spell_effect());
}

public int
start()
{
    set_spell_effect_desc("true hearing");

    if (!::start() || !shadow_me(spell_target))
    {
        remove_spell_effect_object();
        return 0;
    }

    gSkill = (spell_caster->query_priest_level() + 1) * 8;
    gSkill += random(5);

//    alarm = set_alarm(1200.0, 0.0, &dispel_spell_effect());

    return 1;
}
