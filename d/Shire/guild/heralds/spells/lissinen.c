/*
 * Lissinen - ask Este to heal your wounds.
 *
 * May use athelas as an optional herb to increase the power of the spell
 *
 * Arman Kharas, May 2018
 *
 * Updated August 2019 according to revised caid limits
 * for layman magic guilds - Arman
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "heal";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "../herald.h"
#include "/d/Shire/common/defs.h"

#include <macros.h>
#include <tasks.h>

#define HIS(x)        ((x)->query_possessive())
#define HIM(x)        ((x)->query_objective())

#define MAX_HEAL_CAID   50.0

#define HUCKLEBERRY_KEEP_PERCENTAGE  (83)

// Global variables
static mapping special_ingredient = ([]);
public string spell_failure_corruption_check();

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_spell_name("lissinen");
    set_spell_desc("Ask Este to heal your wounds");

    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_fail(spell_failure_corruption_check);

    set_spell_task(TASK_HARD);
    // 1.5 times the standard cast time for a heal spell 
    set_spell_time_factor(1.5);  

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_combat_aid(50.0);

    // Low component cost - multiple casts per herb.
    set_spell_component_factor(COMPONENT_AID_LOW);

}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Heal fail message activated");
    if(!random(4))
        this_player()->spell_failure_corruption_check(query_spell_time());

    return "You fail in your attempt to channel the powers of the Valar.\n";
}

/* 
 * Function:    query_spell_guild_strength
 * Description: This should be overridden by each implementation of
 *              the spell to use elements like guild stat as part of
 *              the guild strength calculation.
 * Returns:     0-100 - scale of the person's strength in the guild.
 *                      Should not exceed 100.
 */
public int
query_spell_guild_strength()
{
    int corruption, level, base_str, str;

    base_str = 40;
    level = 3 * (this_player()->query_herald_level() + 1);
    corruption = min(100, HERALD_CORRUPTION(this_player()));

    str = max(0, min(100, (base_str + level - corruption)));

    // HERALD_DEBUG("Heal strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ".");

    return str;
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{   
    // modify base caid by active maintained spells.
    float total_combat_aid = MAX_HEAL_CAID;
    float available_combat_aid = MAX_HEAL_CAID;

    float caid_mod;

    if (query_spell_apply_whitehit_aid())
    {
        total_combat_aid += itof(query_white_hit_combat_aid());
        available_combat_aid += itof(query_white_hit_combat_aid());
    }

    //  Reduced heal if maintaining a prayer
    if(QUERY_HERALD_MAINTAINING(TP) && 
        (QUERY_HERALD_FOCUS(TP) == "singular"))
    {
    //  Maintaining one buff singular focus, heal reduced by 35 caid
        available_combat_aid -= 35.0;
    }
    else if((QUERY_HERALD_MAINTAINING(TP) > 1) &&
        (QUERY_HERALD_FOCUS(TP) == "dual"))
    {
    //  Maintaining two buffs dual focus, heal reduced by 44 caid
        available_combat_aid -= 44.0;
    }
    else if(QUERY_HERALD_MAINTAINING(TP) > 2)
    {
    //  Maintaining three buffs no focus, heal reduced by 45 caid
        available_combat_aid -= 45.0;
    }
    else if(QUERY_HERALD_MAINTAINING(TP) > 1)
    {
    //  Maintaining two buffs no focus, heal reduced by 30 caid
        available_combat_aid -= 30.0;
    }
    else if(QUERY_HERALD_MAINTAINING(TP))
    {
    //  Maintaining one buff no focus, heal reduced by 15 caid
        available_combat_aid -= 15.0;
    }

    caid_mod = (available_combat_aid / total_combat_aid) * 100.0; 

    // HERALD_DEBUG("Caid modifier: " +ftoi(caid_mod)+ ".");
    return caid_mod;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    if (IS_MEMBER(player))
    {
        return 1;
    }

    return 0;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({ "huckleberry" });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "huckleberry";
}

/*
 * Function name: hook_use_ingredients
 * Description:   This function should return the message that will be printed
 *                to the caster when he/she has used some ingredients.
 * Arguments:     ingrs - The ingredients that will be used.
 * Returns:       The message to print.
 */
public void
hook_use_ingredients(object *ingrs)
{
    object * consumed = ({ });
    foreach(object ob : ingrs) 
    {
        if (random(100) < HUCKLEBERRY_KEEP_PERCENTAGE)
        {
            write("Luckily, you manage to keep all ingredients intact.\n");
            ob->add_prop("_savable_from_consumption", 1);
        }
        else
        {
            consumed += ({ ob });
        }
    }

    consumed = filter(consumed, &->check_seen(this_player()));
    ::hook_use_ingredients(consumed);
}


public void
consume_components(object *ingrs)
{
    foreach (object ingredient : ingrs)
    {
        if (ingredient->query_prop("_savable_from_consumption"))
        {
            this_object()->restore_components(({ ingredient }));
        }
        else
        {
            ingredient->remove_object();
        }
    }
} /* consume_components */

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    // We want to check corruption level here to see if we can channel

    if (HERALD_CORRUPTION(caster) > 75)
    {
        caster->catch_tell("As a fallen Herald, you can no longer " +
            "channel the powers of the Valar.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
  // deliberately kept blank. Healing message covered under concentrate_msg
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message; 
    string reduced_msg = "";
    object target = targets[0];

    //  If already maintaining two blessings, heal combat aid reduced.  
    if(QUERY_HERALD_MAINTAINING(TP) > 1)
    {
        reduced_msg = ", although struggle to do so effectively " +
            "while maintaining two other blessings";
    }

    if(target->query_prop(LIVE_I_UNDEAD))
    {
        caster_message = "You call upon Mandos, Keeper of the Dead, " + 
            "for aid in sending the unliving to the Halls of " +
            "Awaiting" +reduced_msg+ ".\n";
        watcher_message = QCTNAME(caster) + " calls upon Mandos, " +
            "Keeper of the Dead, for aid in sending the unliving to " +
            "the Halls of Awaiting.\n";
    }
    else
    {
        caster_message = "You begin channelling the blessings of Este, " +
            "calling upon her powers of renewal and healing" +
            reduced_msg+ ".\n";
        watcher_message = QCTNAME(caster) + " begins channelling the " +
            "blessings of Este, calling upon her powers of renewal " +
            "and healing.\n";
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid());  
}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    int heal = heal_amounts[0];
    string heal_desc;

    switch(heal)
    {
       case 0..50:
         heal_desc = " slightly";
         break;
       case 51..150:
         heal_desc = " somewhat";
         break;
       case 151..250:
         heal_desc = "";
         break;
       case 251..450:
         heal_desc = " greatly";
         break;
       case 451..750:
         heal_desc = " miraculously";
         break;
       default:
         heal_desc = "";
         break;
    }

    // casting on evil aligned targets results in a standing adjustment.

    if (tar->query_alignment() < -79)
    {
	caster->catch_tell("You feel your actions may be in aid of " +
            "Darkness and putting you at risk of corruption by the " +
            "Shadow of Mordor.\n"); 
        ADD_CORRUPTION(caster, 1);
    }

    if (tar == caster)
    {
	caster->catch_tell("You channel healing energies into your " +
            "body, your wounds" + heal_desc+ " mended.\n");
	tell_room(environment(caster), QCTNAME(caster) + " channels " +
            "healing energies into " + HIS(caster)+ " body, looking" +
            heal_desc+ " mended.\n", targets);
    }
    else
    {
	caster->catch_tell("You channel healing energies towards " +
	    tar->query_the_name(caster) + ", and " + HIS(tar) + 
            " wounds are" +heal_desc+ " mended.\n");
	tar->catch_tell(caster->query_The_name(tar) + " channels " +
	    "healing energies towards you, and your wounds are" +
            heal_desc+ " mended.\n");
	tell_room(environment(caster), QCTNAME(caster) + " channels " +
	    "healing energies towards " + QTNAME(tar) + ", " +
	    HIS(tar) + " wounds" +heal_desc+ " mended.\n",
	    ({ caster, tar }), caster);
    }

    // HERALD_DEBUG("Heal amount: " +heal+ ".");
}

/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    object tar = targets[0];
    int harm = harm_amounts[0];
    string harm_desc;

    switch(harm)
    {
       case 0..50:
         harm_desc = " lightly";
         break;
       case 51..150:
         harm_desc = "";
         break;
       case 151..250:
         harm_desc = " painfully";
         break;
       case 251..450:
         harm_desc = " badly";
         break;
       case 451..750:
         harm_desc = " almost to ash";
         break;
       default:
         harm_desc = "";
         break;
    }

    if (tar == caster)
    {
	caster->catch_tell("You convulse in pain as divine energies "+
	    "are channelled through your body.\n");
	tell_room(environment(caster), QCTNAME(caster) + " convulses as "+
	    "if in some kind of pain.\n", targets);
    }
    else
    {
	caster->catch_tell(tar->query_The_name(caster) + " is burned"  
            + harm_desc +" as you channel " +HIS(tar)+ " unliving " +
            "energy to the Halls of Awaiting.\n");
	tar->catch_tell(caster->query_The_possessive_name(tar) + 
            " attempts to channel your unliving essence to the Halls " +
            "of Awaiting, burning you" + harm_desc +".\n");
	tell_room(environment(caster), QCTPNAME(caster) + " attempts " +
	    "to channel " + QTPNAME(tar) + " unliving essence to the " +
            "Halls of Awaiting, burning " +HIM(tar)+ harm_desc +".\n",
	    ({ caster, tar }), caster);
    }

    // HERALD_DEBUG("Harm amount: " +harm+ ".");
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */

public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You are missing the herb huckleberry to channel lissinen.\n");
}

static mixed * 
check_required_items(object actor, mixed * targets, string arg, int pretest)
{
    mixed *items = ::check_required_items(actor, targets, arg, pretest);
    
    if (sizeof(items) > sizeof(query_heal_ingredients(actor)))
        special_ingredient[actor] = 1;
    else
        special_ingredient[actor] = 0;
    
    return items;
}
