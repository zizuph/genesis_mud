/* 
 * pimprecate - curse ones foe
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

int gAlarm, gTime;

varargs public int
dispell_spell_effect(object dispeller)
{
    query_shadow_who()->catch_tell("You vanquish your inner demons.\n");
    tell_room(environment(query_shadow_who()), QCTNAME(query_shadow_who()) +
        " seems to have regained " + HIS(query_shadow_who()) +
        " confidence.\n", query_shadow_who());

    set_alarm(0.0, 0.0, &remove_spell_effect_object());

    return 1;
}

int
query_pimprecate_object()
{
    return 1;
}

int
query_skill(int snum)
{
    int proc;
    
    /* Hide it to show the original when the command skills is issued */
    if ((snum == SS_PARRY || snum == SS_DEFENCE) &&
        (calling_program() == "cmd/live/state.c" ||
        query_verb() == "skills") || !get_alarm(gAlarm))
        return query_shadow_who()->query_skill(snum);

    proc = (ftoi(get_alarm(gAlarm)[2]) * 100) / gTime;

    switch (snum)
    {
        case SS_PARRY:
            return query_shadow_who()->query_skill(SS_PARRY) -
                ((proc * query_shadow_who()->query_skill(SS_PARRY)) / 100);
        case SS_DEFENCE:
            return query_shadow_who()->query_skill(SS_DEFENCE) -
                ((proc * query_shadow_who()->query_skill(SS_DEFENCE)) / 100);
        default:
            return query_shadow_who()->query_skill(snum);
    }
}

void
set_time(int t)
{
    find_player("stralle")->catch_tell("[PoT] time for imprecation: " + t + "\n");
    find_player("stralle")->catch_tell("[PoT] spell_target: " +
        spell_target->query_name() + "\n");
    gAlarm = set_alarm(itof(t), 0.0, &dispell_spell_effect());
    gTime = t;
}

void
tell_cursed()
{
    string s;
    object at;

    if (!spell_target->query_attack())
        return;

    at = spell_target->query_attack();

    switch (random(5))
    {
        case 0:
            s ="It's no use defending against this onslaught, you are " +
                "much too weak.";
            break;
        case 1:
            s = "You feel overpowered by " +
                at->query_the_name(spell_target) + "'s attack.";
            break;
        case 2:
            s = "How could one such as yourself defend against " +
                at->query_the_name(spell_target) + "?";
            break;
        case 3:
            s = "What use is there to defend against " +
                at->query_the_name(spell_target) + ", " +
                "who would kill you anyway.";
            break;
    }
    
    if (strlen(s))
    {
        spell_target->catch_tell(s + "\n");
        if (!random(3))
            tell_room(environment(spell_target), QCTNAME(spell_target) +
                " seems careless about defending " + HIM(spell_target) +
                "self.\n", spell_target);
    }
}

public int
start()
{
    set_spell_effect_desc("curse");

    if (!::start() || !shadow_me(spell_target))
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->catch_tell("You feel weak and defenceless.\n");

    set_alarm(7.0, 7.0, &tell_cursed());
    
//    alarm = set_alarm(1200.0, 0.0, &dispel_spell_effect());

    return 1;
}
