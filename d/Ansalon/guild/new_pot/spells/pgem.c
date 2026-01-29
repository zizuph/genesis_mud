/*
 * pGem
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>  
#include <cmdparse.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";
inherit GUILDDIRSPELL + "common";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 11;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;
    string watcher_message;
    
    set_this_player(caster);
    caster->catch_tell("You begin to intone a prayer to the Queen " +
        "of Darkness.\n");
    watcher_message = QCTNAME(caster) + " begins to intone a prayer.\n";
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    set_this_player(old_tp);
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
    object tar, gem;
    int pot_level = min(15, (caster->query_skill(PS_GUILD_LEVEL) / 10 + 1));

    if (!sizeof(targets))
    {
    	caster->catch_tell("No such item present to be transformed by pgem.\n");
    	return;
    }
    tar = targets[0];

    if (!tar)
    {
    	caster->catch_tell("Oops, it seems the object has disappeared!\n");
    	return;
    }

    if (!tar->id("gem"))
    {
    	caster->catch_tell("The object of the transformation must be a " +
    	"gem to start with!\n");
    	return;
    }

    if (tar->query_prop(MAGIC_AM_MAGIC))
    {
    	caster->catch_tell("The gem resists the transformation.\n");
    	return;
    }

    setuid();
    seteuid(getuid());
    gem = clone_object(SOULGEM_OBJ);

    // DEBUG("Pgem PoT level: " +pot_level+".");
    gem->set_priest_level(caster, pot_level);
    gem->move(E(tar),1);

    if (E(gem) == caster)
    {
        caster->catch_tell("The " + tar->short() + " shines brightly, and " +
            "when the light fades, it has changed to " +
            LANG_ADDART(gem->short()) + ".\n");
        tell_room(environment(caster), "An unholy light shines for a while " +
            "between " + QTNAME(caster) + "'s hands.\n", ({ caster }), caster);
    }
    else
    {
        tell_room(E(gem),"The " + tar->short() + " shines brightly, and " +
        "when the light fades, it has changed to " +
        LANG_ADDART(gem->short()) + ".\n");
    }

    if (tar->query_prop(HEAP_I_IS))
    {
        tar->set_heap_size(tar->num_heap() - 1);
    }
    else
    {
        tar->remove_object();	
    }
}

public object *
pgem_target(object caster, string str)
{
    object *arr;

    if (!stringp(str))
    {
        caster->catch_tell("You need a target.\n");
        return ({ });
    }
    
    arr = FIND_STR_IN_OBJECT(str, caster);
    if (!sizeof(arr))
    {
        caster->catch_tell("You need a target.\n");
        return ({ });
    }
    
    if (sizeof(arr) >= 2)
    {
        caster->catch_tell("Multiple targets would probably be a bad idea.\n");
        return ({ });
    }
    
    if (!arr[0]->id("gem"))
    {
        caster->catch_tell("The target must be a gem.\n");
        return ({ });
    }

    return arr;
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("pgem");
    set_spell_desc("Create a soul gem out of an ordinary gem");

    set_spell_element(SS_ELEMENT_EARTH, 15);
    set_spell_form(SS_FORM_TRANSMUTATION, 35);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_vocal(1);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_time(15);
    set_spell_mana(110);
    set_spell_ingredients(({"skullcap","heart"}));

    set_spell_class(SPELL_CLASS_1);
    set_spell_task(TASK_SIMPLE);

    set_spell_target(spell_target_present_objects);
    set_ability_target_verify(spell_verify_present); 
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