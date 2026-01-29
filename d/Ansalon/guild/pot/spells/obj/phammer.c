/*
 * phammer - enchant club.
 */

#include "../../guild.h"
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

int gAlarm, gPen, gHit, gSkill, gSkill_raised;

varargs public int
dispell_spell_effect(object dispeller)
{
    object *obs, holder = environment(spell_target);

    if (living(holder))
    {
        holder->catch_tell("The glow around your " +
            spell_target->query_name() + " fades away.\n");

        obs = all_inventory(environment(holder));
        obs -= FILTER_IS_SEEN(holder, obs);
        obs += ({ holder });

        tell_room(environment(holder), "The glow around the " +
            spell_target->query_name() + " held by " + QTNAME(holder) +
            " fades away.\n", obs, holder);
    }
    else
    {
        tell_room(holder, "The glow around the " +
            spell_target->query_name() + " fades away.\n");
    }

    set_alarm(180.0 - (itof(random(10) * 10)), 0.0,
         &remove_spell_effect_object());

/* Vencar 01-02-2004 e.g. gHit -= -15 doesn't that give a + of 15?

    gHit -= (gHit - 20);
    gPen -= (gPen - 20);
*/
#ifdef 0
    gHit = -2;
    gPen = -2;
#endif

    /* This is just a temporary change as per the alarm above
     * that there is a degrading effect for some time after the
     * true effect. This is how it is supposed to be! /Stralle
     */

    gHit -= 20;
    gPen -= 20;

    if (gSkill_raised)
    {
        if (query_shadow_who()->query_wielded())
        {
            (query_shadow_who()->query_wielded())->set_skill_extra(SS_WEP_CLUB,
                (query_shadow_who()->query_wielded())->query_skill_extra(SS_WEP_CLUB) -
                gSkill_raised);
            gSkill_raised = 0;
        }
    }
    
    return 1;
}

int
query_phammer_object()
{
    return (pointerp(get_alarm(gAlarm)) ? 1 : -1);
}

int
query_hit()
{
    return query_shadow_who()->query_hit() + gHit;
}

int
query_pen()
{
    return query_shadow_who()->query_pen() + gPen;
}

void
set_time(int t)
{
    gAlarm = set_alarm(itof(t), 0.0, &dispell_spell_effect());
}

void
set_skill(int s)
{
    gSkill = s;
}

mixed
wield(object obj)
{
    mixed r, aaa;
    
    r = query_shadow_who()->wield(obj);

    /* If the true effect has passed, don't raise the skill
     */
	aaa = get_alarm(gAlarm); //this should fix the runtime error Milan 22.6.2004
    if (!pointerp(aaa) || !aaa[2])
        return r;
    
    if (intp(r) && r >= 0)
    {
        if (this_player()->query_alignment() >= -100)
        {
            this_player()->heal_hp(-150);
            return "As you grip the " + query_shadow_who()->short() +
                " you get a shock and are forced to let go of it.\n";
        }

        /* Never raise it above superior guru
         */
        gSkill_raised = min(100, this_player()->query_skill(SS_WEP_CLUB) +
            gSkill) - this_player()->query_skill(SS_WEP_CLUB);
        this_player()->set_skill_extra(SS_WEP_CLUB,
            this_player()->query_skill_extra(SS_WEP_CLUB) + gSkill_raised);
    }
    
    return r;
}

mixed
unwield(object obj)
{
    mixed r;
    
    r = query_shadow_who()->unwield(obj);
    
    if (intp(r) && r >= 0)
    {
        if (gSkill_raised)
        {
            (query_shadow_who()->query_wielded())->set_skill_extra(SS_WEP_CLUB,
                (query_shadow_who()->query_wielded())->query_skill_extra(SS_WEP_CLUB) -
                gSkill_raised);
            gSkill_raised = 0;
        }
    }

    return r;
}

public int
start()
{
    object wielder;

    set_spell_effect_desc("hammer");
    if (!::start() || !shadow_me(spell_target))
    {
        remove_spell_effect_object();
        return 0;
    }

    switch (spell_caster->query_priest_level())
    {
        case 2:
            gHit = 15;
            gPen = 15;
            break;
        case 1:
            gHit = 10;
            gPen = 10;
            break;
        default:
            gHit = 5;
            gPen = 5;
    }

    if (!query_shadow_who()->query_wf())
        query_shadow_who()->set_wf(query_shadow_who());

    if (query_shadow_who()->query_wielded() &&
        (query_shadow_who()->query_wielded())->query_alignment() < -100)
    {
        wielder = query_shadow_who()->query_wielded();

        /* Never raise it above superior guru
         */
        gSkill_raised = min(100, wielder->query_skill(SS_WEP_CLUB) +
            gSkill) - wielder->query_skill(SS_WEP_CLUB);
        wielder->set_skill_extra(SS_WEP_CLUB,
            wielder->query_skill_extra(SS_WEP_CLUB) + gSkill_raised);
    }

/* Added 1-2-2004 by Vencar due to new balance maximum of 50 for onehanded
   clubs and 60 for twohanded clubs*/
/*    if (query_shadow_who()->query_hands() == W_BOTH)
        lWepMax = 60;
    else
        lWepMax = 50;
*/
    if (query_shadow_who()->query_hands() == W_BOTH)
    {
        if (query_shadow_who()->query_pen() + gPen > 60)
            gPen = MIN(gPen, 60 - query_shadow_who()->query_pen() );
        if (query_shadow_who()->query_hit() + gHit > 60)
            gHit = MIN(gHit, 60 - query_shadow_who()->query_hit() );
    }
    else
    {
        if (query_shadow_who()->query_pen() + gPen > 50)
            gPen = MIN(gPen, 50 - query_shadow_who()->query_pen() );
        if (query_shadow_who()->query_hit() + gHit > 50)
            gHit = MIN(gHit, 50 - query_shadow_who()->query_hit() );
    }

//    alarm = set_alarm(1200.0, 0.0, &dispel_spell_effect());

    return 1;
}

public varargs string
long(string str, object for_obj)
{
    if (get_alarm(gAlarm))
        return query_shadow_who()->check_call(query_shadow_who()->query_long()) +
        "The weapon has a spiritual glow about it.\n";

    return query_shadow_who()->check_call(query_shadow_who()->query_long());
}
