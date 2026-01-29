/*
 * pHeal
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "heal";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"
#include <wa_types.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"

inherit GUILDDIRSPELL + "common";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#define TEMP_I_COMPONENT_CHECKED "_temp_i_component_checked"
#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()

#define PHEAL_MAX_CAID 150.0

mapping used_soul_gem = ([]);

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 7;
}

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_spell_name("pheal");
    set_spell_desc("Healing of yourself or others");

    set_spell_element(SS_ELEMENT_LIFE, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);
    // 1.5 times the standard cast time for a heal spell 
    set_spell_time_factor(1.5);  

    set_spell_combat_aid(PHEAL_MAX_CAID);

    // High component cost until access to pgem which reduces
    // cost to low.
    set_spell_component_factor(COMPONENT_AID_LOW);
}


public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    ::hook_no_ingredients_fail(ingredients_needed);
    used_soul_gem[this_player()] = 0;
}

/*
 * Function:    ignore_ability_ingredients
 * Description: Function that allows a person to ignore ability ingredients
 *              By default, npcs and wizards who have a special property
 *              set will be able to ignore ability ingredients.
 */
public int
ignore_ability_ingredients(object caster)
{
    object gem;

    // DEBUG("pheal components: can ignore checked.");

    if (!objectp(caster))
    {
        return 0;
    }
    
    if (!objectp(gem = P(MEDALLION_ID, caster)->query_soul_gem()))
    {
        return 0;
    }
    // DEBUG("pheal components: bypassed used soul gem.");

    if (gem->query_charge() < 100)
    {
        if (!used_soul_gem[caster])
        {
            caster->catch_tell("The " + gem->short() + " doesn't " +
            "have enough energy remaining from captured souls, " +
            "so you resort to your prayer components.\n");
        }
        // DEBUG("ptalon components: not enough charge checked.");
        used_soul_gem[caster] = -1;
        return 0;
    }

    if (gem->query_charge() >= 100)
    {
        if (used_soul_gem[caster])
        {
            if (calling_function(-3) == "execute_ability" && used_soul_gem[caster] < 0)
            {
                used_soul_gem[caster] = 100;
                gem->add_charge(-100);
                caster->catch_tell("The " + gem->short() + " throbs as you " +
                "draw from the energy of your captured souls.\n");
            }
        
            return 1;
        }
        
        used_soul_gem[caster] = -1;
        return 1;
    }
    
    return 0;
}

object
herb_ingr(object *possible, object *found) 
{
    object *list, comp;
    int i;
    
    list = possible - found;
    for (i = 0; i < sizeof(list); i++)
    {
        if (member_array(list[i]->query_herb_name(),
            ({ "horsetail", "chokecherry" })) > -1 &&
            filter_components(list[i], this_player()))
        {
            if (list[i]->query_prop(HEAP_I_IS))
                prepare_heap_component(list[i]);
            
            comp = list[i];
            break;
        }
    }
    
    return comp;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({ "heart", herb_ingr });
//    return ({ "heart", "horsetail" });
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
    /* intentionally empty */
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

    // Clear soul gem check
    used_soul_gem[caster] = 0;

    // casting on good aligned targets results in a standing adjustment.

    if (tar->query_alignment() > 100)
    {
        caster->catch_tell("You find it more difficult healing someone not " +
	    "dark of heart, and feel less in touch with Takhisis.\n");
        caster->adjust_standing(RND_RANGE(-70, 20));
    }

    if (tar == caster)
    {
        caster->catch_tell("You feel new health infusing your body.\n");
        tell_room(environment(caster), QCTNAME(caster) +
	    " straightens up, looking more hale.\n", targets);
    }
    else
    {
        caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " shivers as " + HIS(tar) + " wounds are healed.\n");
        tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you shiver as your " +
	    "wounds are healed.\n");
        tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " shivers as " + HIS(tar) + " wounds are healed.\n",
	    ({ caster, tar }), caster);
    }

    // DEBUG("Heal amount: " +heal+ ".");
    GUILD_ADMIN->log(caster, "pheal", tar->query_real_name() + ": " + heal);
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

    // Clear soul gem check
    used_soul_gem[caster] = 0;

    if (tar == caster)
    {
        caster->catch_tell("You convulse in pain as dark energies shoot "+
	    "through your body.\n");
        tell_room(environment(caster), QCTNAME(caster) + " convulses as if "+
	    "in some kind of pain.\n", targets);
    }
    else
    {
        caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " convulses in pain.\n");
        tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you feel painful " +
	    "energies shoot through your body.\n");
        tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " convulses in pain.\n",
	    ({ caster, tar }), caster);
    }
}



/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public nomask float
query_spell_combat_aid_modifier()
{
    float pot_standing = itof(min(1000, this_player()->query_skill(PS_STANDING)));

    // need to modify the heal caid taking in to account the white
    // damage component and the set_caid component.

    int wd_caid = query_white_hit_combat_aid();
    int max_caid = ftoi(PHEAL_MAX_CAID) + wd_caid;

    // Base caid is the white damage component of the maximum 
    // caid which should be 100 * 100 / 230 = 43.5

    float modifier = itof(100 * wd_caid / max_caid);

    // The Dark Lady base heal is 90 caid (60.0% of max caid), 
    //                      up to 150 (100% of max) if not using pbless.
    // The Dark Warrior has a 20 caid heal (13.3% of max).


    if (this_player()->query_prop(DARK_LADY_ASPECT))
    {
        if (!this_player()->query_prop("pot_bless_subloc"))
            modifier += 100.0 * PHEAL_MAX_CAID / itof(max_caid);
        else
            modifier += 60.0 * PHEAL_MAX_CAID / itof(max_caid);
    }
    else
        modifier += 13.3 * PHEAL_MAX_CAID / itof(max_caid);

    modifier = modifier * pot_standing / 1000.0;

    return min(100.0, modifier);
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

