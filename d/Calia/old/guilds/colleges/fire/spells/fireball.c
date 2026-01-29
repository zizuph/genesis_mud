/*

  This is the fireball spell for the College of Fire Magic. It is a 
  standard bolt spell, save for one thing: it can destroy lesser 
  armours worn by the target.

  Coded by Bishop of Calia, July 2003

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spells/bolt.c";
inherit "/d/Calia/guilds/colleges/specials/common_functions";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "defs.h"


public object*
special_target_one_other_present_living(object caster, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    
    oblist = PARSE_THIS(str,"[at] / [on] [the] %l");
        
    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only "+
            "select one target.\n");
        return ({});
    }

    /*
       Add check for correct potion imbibed here.
    */

    return oblist;
}


int 
bolt_pen(object ob)
{
    int stat = find_controlling_stat("fire", ob);
    
    //Penetration 600-1200.
    return min(600 + 3*(random(stat) + random(stat)), 1200);
}


/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);

    set_spell_time(4);
    set_spell_mana(160);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 65);
    set_spell_form(SS_FORM_CONJURATION, 65);
    set_spell_ingredients(({ }));
    
    set_spell_target(special_target_one_other_present_living);

    set_bolt_pen(bolt_pen(caster));
    set_spell_name("fireball");
    set_spell_desc("Launch a fireball at someone");
    
    return 0;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You draw power from the Plane of Fire.\n");
    say(QCTNAME(caster) + " appears to focus, " + 
        caster->query_possessive() + " eyes flashing deep red.\n");
}

/*
 * Function name: desc_bolt_miss
 * Description:   Write out some text describing the missed attack.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_miss(object caster, object target)
{
    caster->catch_tell(target->query_The_name(caster) + " quickly hits" +
        " the ground, the flaming mass passing right over " + 
        target->query_objective() + ".\n");
    caster->tell_watcher(QCTNAME(target) + " quickly hits the ground, the" +
        " flaming mass passing right over " + target->query_objective() + 
        ".\n", target);     
    target->catch_tell("You quickly hit the ground, the flaming mass passing" +
        " right over you.\n");
}


/*
 * Function name: desc_bolt_cast
 * Description:   Describe casting of the spell, not including damage messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_cast(object caster, object *targets)
{
    caster->catch_tell("You finish the spell and a great flaming" +
        " mass appears before you. As you fix your concentration upon " +
        targets[0]->query_the_name(caster) + ", the mass shudders, then" +
        " streaks with blinding speed towards your hapless target," +
        " threatening to swallow " + targets[0]->query_objective() + " up.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes the spell and a great" +
        " flaming mass appears before " + caster->query_objective() + ". As " +
        caster->query_pronoun() + " fixes " + caster->query_possessive() +
        " concentration upon " + QTNAME(targets[0]) + ", the mass shudders," +
        " then streaks with blinding speed towards the hapless target," +
        " threatening to swallow " + targets[0]->query_objective() + " up.\n",
        targets[0]);
    targets[0]->catch_tell(caster->query_The_name(targets[0]) + " finishes" +
        " the spell and a great flaming mass appears before " + 
        caster->query_objective() + ". As " + caster->query_pronoun() + 
        " fixes " + caster->query_possessive() + " concentration upon you," +
        " the mass shudders, then streaks with blinding speed towards you," +
        " threatening to swallow you up!\n");
}


/*
 * Function name: try_to_hit
 * Description:   Test to see if the bolt hits a target.
 * Arguments:     object caster - the caster
 *                object target - the target
 * Returns:       1/0 - hit/missed
 */
public int
try_to_hit(object caster, object target)
{
    int stat = find_controlling_stat("fire", caster);

    int taskdiff = max(0, TASK_ROUTINE - 100 - stat);
   
    return (caster->resolve_task(taskdiff, ({SS_INT, SKILL_WEIGHT, 70,
        SS_ELEMENT_FIRE, SKILL_WEIGHT, 30, SS_FORM_CONJURATION}), 
        target, ({TS_DEX, SKILL_WEIGHT, 70, SS_DEFENCE, SKILL_WEIGHT, 
        30, SS_ACROBAT})) > 0);
}

public void
destroy_armours(object target)
{
    object *armours;
    int i;

    i = 0;
    armours = target->query_clothing(-1);

    while (i < sizeof(armours))
    {
        if (armours[i]->query_ac() <= 20 && 
            !armours[i]->query_auto_load() &&
            armours[i]->query_prop(OBJ_I_RES_FIRE) < 30)
        {
            tell_room(environment(target), "The " + armours[i]->query_name() +
                " worn by " + QTNAME(target) + " is consumed by the flames!\n",
                target);
            target->catch_tell("The " + armours[i]->query_name() + " you're" +
                " wearing is consumed by the flames!\n");
            armours[i]->remove_object();
        }
        
        i++;
    }
}

/*
 * Function name: desc_bolt_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_bolt_damage(object caster, object target, mixed *result)
{
    object skeleton;
    string how, how2;
   
    switch(result[0])
    {
        case 0:
            how = "leaving " + target->query_objective() + " blackened by" +
                " soot, but otherwise unharmed.\n";
            how2 = "leaving you blackened by soot, but otherwise unharmed.\n";
            break;
        case 1..8:
            how = "scorching " + target->query_objective() + " lightly.\n";
            how2 = "scorching you lightly.\n";
            break;
        case 9..15:
            how = "searing " + target->query_objective() + " and leaving some" +
                " painful blisters.\n";
            how2 = "searing you and leaving some painful blisters.\n";
            break;
        case 16..25:
            how = "leaving " + target->query_objective() + " roasted by" +
                " the powerful salvo.\n";
            how2 = "leaving you roasted by the powerful salvo.\n";
            break;
        case 26..50:
            how = "disfiguring " + target->query_objective() + " as the" +
                " flames leave marks, burns wounds and blisters over " +
                target->query_possessive() + " entire body.\n";
            how2 = "disfiguring you as the flames leave marks, burn wounds" +
                " and blisters over your entire body.\n";
            break;
        default:
            how = "the incredible heat causing " + target->query_possessive() +
                " skin to melt off in" +
                " several places, leaving " + target->query_objective() +
                " a ragged, horribly disfigured copy of " + 
                target->query_possessive() + " former self.\n";
            how2 = "the incredible heat causing your skin to melt off in" +
                " several places, leaving you a ragged, horribly disfigured" +
                " copy of your former self.\n";
    }
    
    if (target->query_hp() <= 0)
    {
        how = "enveloping " + target->query_objective() + " and completely" +
            " obscuring " + target->query_objective() + " from view. As the" +
            " flames dissipate, only a blackened skeleton that quickly" + 
            " clatters to the ground is left of " + target->query_objective() +
            "\n";
        how2 = "enveloping you completely. Your last sensation is" +
            " unbearable pain as the flesh burns from your body.\n";
            
        seteuid(getuid());
        skeleton = clone_object(FIRE_OBJECTS + "skeleton_obj");
        skeleton->set_race(target->query_race_name());
        skeleton->move(environment(caster));
        target->add_prop(LIVE_I_NO_CORPSE, 1);            
    }
    
    caster->catch_tell("The great flaming mass impacts with " + 
        target->query_the_name(caster) + ", " + how);
    caster->tell_watcher("The great flaming mass impacts with " + 
        QTNAME(target) + ", " + how, target);
    target->catch_tell("The great flaming mass impacts with you, " + how2);
    
    destroy_armours(target);
}



/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You complete the spell, but the flame you" +
            " summon is immediately doused by the surrounding water!\n");
    }
    else
    {
        ::resolve_spell(caster, targets, resist, result);
    }
}