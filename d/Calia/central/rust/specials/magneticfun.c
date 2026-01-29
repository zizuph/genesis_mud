/* This is the alchemist's magnetic spell, coded by Bishop 4.1.99
in Calia. It's supposed to target the enemy you're fighting
then have all the other enemies slam into that enemy, damaging
the lot of them. If there's only one enemy, he'll throw explosive
potions instead. */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "defs.h"

public int
create_spell_magneticfun(object caster, object *targets, 
    string argument)
{
    set_spell_time(3);
    set_spell_mana(150);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_EARTH, 0);
    set_spell_form(SS_FORM_ENCHANTMENT, 0);
    set_spell_ingredients(({ })); // No point in components here.
    set_spell_offensive(1);
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    return 0;
}

public void
magneticfun(object caster, object *targets, int *resist, int result)
{
    int r, i, targetpen;
    string how, *hitresult;
    object *friends;

    friends = caster->query_enemy(-1);
    friends -= ({targets[0]});
    r = sizeof(friends);
    targetpen = r * 700;

    if (r == 0)
    {
        return;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your" +
            " target is unaffected.\n");
        return;
    }

    tell_room(environment(caster), QCTNAME(caster) + " completes" +
        " the spell and points at " + QTNAME(targets[0]) + "." +
        " There is a great rumble, and a flickering grey sphere" +
        " briefly surrounds " + QTNAME(targets[0]) + ". With a" +
        " rush of air, all others who are" +
        " fighting " + QTNAME(caster) + " are torn from where they" +
        " are standing and suddenly catapulted towards " + 
        QTNAME(targets[0]) + " with brutal force!\n", targets[0]);

    targets[0]->catch_msg(QCTNAME(caster) + " completes the" + 
        " spell and points at you. Suddenly you are surrounded" +
        " by a flickering grey sphere, and the world seems blurred."+
        " The sphere disappears, and a split second later, all" +
        " others who were fighting " + QTNAME(caster) + " are" +
        " torn from where they were standing with a rush of air" +
        " and catapulted towards you with brutal force!\n");

    hitresult = targets[0]->hit_me(targetpen, W_BLUDGEON, caster, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "not harmed";
            break;
        case 1..5:
            how = "slightly bruised";
            break;
        case 6..10:
            how = "very bruised";
            break;
        case 11..20:
            how = "seriously beat up";
            break;
        case 21..50:
            how = "smashed senseless";
            break;
        default:
            how = "crushed almost to a pulp";
            break;
    }
        
    if (targets[0]->query_hp() <= 0)
    {
        how = "thrown to the ground in a lifeless heap" +
                " after the violent impact";
    }

    tell_room(environment(targets[0]), QCTNAME(targets[0]) + 
        " is " + how + ".\n", targets[0]);
    targets[0]->catch_msg("You are " + how + ".\n");

    for(i=0; i < r; i++)
    {
        hitresult = friends[i]->hit_me(700, W_BLUDGEON, caster, -1);
        switch (hitresult[0])
        {
            case 0:
                how = "not harmed";
                break;
            case 1..5:
                how = "slightly bruised";
                break;
            case 6..10:
                how = "very bruised";
                break;
            case 11..20:
                how = "seriously beat up";
                break;
            case 21..50:
                how = "smashed senseless";
                break;
            default:
                how = "crushed almost to a pulp";
                break;
        }
        
        if (friends[i]->query_hp() <= 0)
        {
            how = "thrown to the ground in a lifeless heap" +
                " after the violent impact";
        }

        tell_room(environment(friends[i]), QCTNAME(friends[i]) + 
            " is " + how + ".\n", friends[i]);
        friends[i]->catch_msg("You are " + how + ".\n");
    }

    if (targets[0]->query_hp() <= 0)
    {
        targets[0]->do_die(caster);
    }

    for(i=0; i < r; i++)
    {
        if(friends[i]->query_hp() <= 0)
        {
            friends[i]->do_die(caster);
        }
    }
}    


