/*
 * pCurse
 */
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "illfortunate";

#include "../guild.h"
#include "../spells.h"

inherit GUILDDIRSPELL + "common";

#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define ACTIVE_CURSE "_pot_curse_active"
#define BLIND_CURSE "_pot_blind_curse"

#define LILY_KEEP_PERCENTAGE (83)


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int 
query_spell_level(void)
{
    return 10;
}

/*
 * Function:    config_illfortunate_spell
 * Description: Config function for illfortunate spell. Redefine this in your
 *              own illfortunate spells to override the defaults.
 */
public void
config_illfortunate_spell(void)
{
    set_spell_name("pcurse");
    set_spell_desc("Curse your foe");

    set_spell_element(SS_ELEMENT_LIFE,  40);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);    

    // 1 herb per dozen cast effects that last < 30 seconds
    set_spell_component_factor(COMPONENT_AID_LOW);
    set_spell_combat_aid(45);

    // Spell effect object
    set_shadow_filename(GUILDDIRSPELL + "obj/pcurse_obj");
}

/*
 * Function: query_illfortunate_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments: The caster of this spell
 */
public string *
query_illfortunate_ingredients(object caster)
{
    return ({ "tiger lily" });
}


public int 
check_valid_action(object caster, mixed *targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Warrior, you " +
           "cannot call upon this curse.\n");
        return 0;
    }

    object *target;

    if (targets[0]->query_prop(ACTIVE_CURSE))
    {
        caster->catch_tell("A curse has already been cast " +
	    "upon "+ COMPOSITE_LIVE(targets) +".\n");
        return 0;
    }

    if (caster->query_prop(DARK_LADY_ASPECT) &&
        targets[0]->query_prop(BLIND_CURSE))
    {
            caster->catch_tell("While under the aspect of the Dark Lady " +
             "you cannot curse a foe affected by pblind.\n");
      return 0;
    }

    if (caster->query_prop(DARK_LADY_ASPECT) &&
        (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun()))))
    {
        if(target[0]->query_pot_cooldown())
            return 1;
   
        caster->catch_tell("While under the aspect of the Dark Lady " +
           "you cannot curse a foe affected by ppain.\n");
        return 0;
    }
        
    return 1;
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
        if (random(100) < LILY_KEEP_PERCENTAGE)
        {
            ob->add_prop("_savable_from_consumption", 1);
        }
        else
        {
            consumed += ({ ob });
        }
    }

    consumed = filter(consumed, &->check_seen(this_player()));
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

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_illfortunate(object caster, object* targets)
{
    object tar = targets[0];
    string s = "In the name of Takhisis, Queen of Darkness, by Zeboim of the " +
	"Deep Seas and Chemosh the Lord of Death, by Sargonnas the Dark " +
	"Vengeance, be you cursed!";

    caster->catch_tell("You point at " + tar->query_the_name(caster) +
	" and utter in a cold voice: " + s + "\n");

    tar->catch_tell(caster->query_The_name(tar) + " points at you and " +
	"utters in a cold voice: " + s + "\n");

    tell_room(environment(caster), QCTNAME(caster) + " points at " +
	QTNAME(tar) + " and utters in a cold voice: " + s + "\n",
	({ caster, tar }), caster);
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */

public void
hook_already_has_spell_object(object caster, object target) 
{
    caster->catch_msg(QCTNAME(target) + " is already cursed!\n");
}

/*
 * Function:    hook_curse_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_illfortunate_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " is " +
	"unaffected by your curse.\n");
    targets->catch_msg("You resist an attempt by " + QTNAME(caster) +
	"to curse you.\n");
    caster->tell_watcher(QCTPNAME(caster) + " invocation of a curse was " +
	"resisted by " + COMPOSITE_LIVE(targets) + ".\n",
	({ caster }) + targets); 
}


/*
 * Function:    resolve_illfortunate_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_illfortunate_spell(object caster, mixed * targets, int * resist,
                           int result, mapping spell_input)
{
    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id(MEDALLION_ID))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name:   query_ability_hit
 * Description:     Returns the set ability to-hit value.
 * Arguments:       (object) actor
 *                  (mixed) target
 *                  (object *) items
 * Returns:         (int) ability hit value
 */
public int
query_ability_hit(object actor, mixed target, object * items)
{
    if (calling_function() == "query_spell_tohit")
    {
        // harder to cast on when in poor standings
        if (actor->query_skill(PS_STANDING) < -900)
            return convert_task_to_hit(TASK_FORMIDABLE);
    
        if (actor->query_skill(PS_STANDING) < -300) 
            return convert_task_to_hit(TASK_HARD);
    }
    
    return ::query_ability_hit(actor, target, items);
} /* query_ability_hit */

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed *
check_required_items(object actor, mixed * targets,string arg, int pretest)
{
    return filter(actor->query_clothing(-1), &is_valid_medallion(actor,));
}

/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}

/*
 * Function name:   query_ability_item_modifier
 * Description:     
 * Arguments:       1. (object) actor
 *                  2. (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public int
query_ability_item_modifier(object caster, mixed *items)
{
    items = filter(items, &is_valid_medallion(caster,));
    
    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!sizeof(items))
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    
    return 100;
} /* query_ability_item_modifier */