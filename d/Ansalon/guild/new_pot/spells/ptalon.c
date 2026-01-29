/*
 * pTalon
 *
 * Modified to new magic system July 2016 - Arman
 */
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";


#include "../guild.h"
#include "../spells.h"

inherit GUILDDIRSPELL + "common";

#include <alignment.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"

#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()

#define PTALON_MAX_CAID 150.0

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
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 */
public void
config_harm_spell(void)
{
    set_spell_name("ptalon");
    set_spell_desc("Summon talons of dragons to slash your foe");

    set_spell_element(SS_ELEMENT_LIFE, 50);
    set_spell_form(SS_FORM_CONJURATION, 20);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);

    // 1.5 times the standard cast time for a harm spell 
    set_spell_time_factor(1.5); 

    set_spell_combat_aid(PTALON_MAX_CAID);

    // High component cost until access to pgem which reduces
    // cost to low.
    set_spell_component_factor(COMPONENT_AID_LOW);
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
    
    if (::ignore_ability_ingredients(caster))
    {
        return 1;
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

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need a nail and a willow herb to be able to cast ptalon.\n");
    used_soul_gem[this_player()] = 0;
}

object
herb_ingr(object *possible, object *found)
{
    object *list, pl;
    int i;
    
    list = possible - found;
    for (i = 0 ; i < sizeof(list) ; i++)
    {
        if (living(environment(list[i])))
            pl = environment(list[i]);
        else if (living(environment(environment(list[i]))))
            pl = environment(environment(list[i]));
        else if (living(environment(environment(environment(list[i])))))
            pl = environment(environment(environment(list[i])));
        else
            continue;

        if (!IS_HERB_OBJECT(list[i]))
            continue;

        if (list[i]->do_id_check(pl) &&
            wildmatch("*willow", list[i]->query_herb_name()) == 1)
            return list[i];
    }
    
    return 0;
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{ 
    string comp = "grey willow";
    mixed comps;
    if (comps = find_components(caster, ({ comp })))
        restore_components(comps);
    
    if (!comps)
        comp = "beach willow";
    
    return ({ "nail", comp });
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string how, ohow; 
    object tar = target; 

    // Clear soul gem check
    used_soul_gem[caster] = 0;

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int dam = result[3];

    if (result[0] < 1)
    {
        caster->catch_tell("Drawing the darkness closer to you, you begin " +
            "to form with your mind the shape of a dragon's talon. Sharp " +
            "and lethal, you strike it against " +
            tar->query_the_name(caster) + ", slashing " + HIM(tar) + " with " +
            "no apparent effect only to disappear again.\n");
        tar->catch_tell("You see the shadows solidify into a dark shape " +
            "above you. You realize what it is just as a dark talon " +
            "relentlessly slashes down upon you, apparently doing no harm " +
            "and is gone just as quickly as it appeared.\n");
        caster->tell_watcher("Dark shadows begin to form above " + QTNAME(tar) +
            " which takes shape to form a dark talon relentlessly slashing " +
            "down upon " + HIM(tar) + ", apparently doing no harm and is " +
            "gone just as quickly as it appeared.\n", ({ caster, target }));

        return;
    }

    switch (result[0])
    {
        case 1..2:
            how = "scratches " + HIS(tar) + " flesh";
            ohow = "scratches your flesh";
            break;
        case 3..5:
            how = "draws trickles of blood";
            ohow = how;
            break;
        case 6..15:
            how = "tears into " + HIS(tar) + " flesh";
            ohow = "tears into your flesh";
            break;
        case 16..40:
            how = "slashes deep wounds in " + HIS(tar) + " flesh";
            ohow = "slashes deep wounds in your flesh";
            break;
        case 41..75:
            how = "rips open a gash in " + HIS(tar) + " flesh";
            ohow = "rips open a gash in your flesh";
            break;
            break;
        default:
            how = "makes bones visible";
            ohow = how;
            break;
    }

    caster->catch_tell("Drawing the darkness closer to you, you begin " +
        "to form with your mind the shape of a dragon's talon. Sharp " +
        "and lethal, you strike it against " +
        tar->query_the_name(caster) + " that relentlessly " + how +
        " only to disappear again.\n");
    tar->catch_tell("You see the shadows solidify into a dark shape " +
        "above you. You realize what it is just as a dark talon " +
        "relentlessly " + ohow + " and is gone just as quickly " +
        "as it appeared.\n");
    caster->tell_watcher("Dark shadows begin to form above " + QTNAME(tar) +
        " which takes shape to form a dark talon relentlessly slashing " +
        "down upon " + HIM(tar) + " which " + how + " and is gone just " +
        "as quickly as it appeared.\n", ({ caster, target }));

    // DEBUG("ptalon damage: " +dam+ ".");
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
    // DEBUG("Ptalon result: " +result+ ".");
    // Clear soul gem check
    used_soul_gem[caster] = 0;
    
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
        if (pointerp(target) && objectp(target[0]))
            target = target[0];
            
        int in_neraka = wildmatch("/d/Ansalon/taman_busuk/neraka/*",
            file_name(environment(actor)));
        
        if (in_neraka || (living(target) && target->id("_warfare_npc_")))
            return convert_task_to_hit(TASK_HARD);
        
        // harder to cast on when in poor standings
        if (actor->query_skill(PS_STANDING) < -900)
            return convert_task_to_hit(TASK_FORMIDABLE);
    
        if (actor->query_skill(PS_STANDING) < -300) 
            return convert_task_to_hit(TASK_DIFFICULT);
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
/*
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}
*/

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

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public nomask float
query_spell_combat_aid_modifier()
{
    float pot_standing = itof(min(1000, this_player()->query_skill(PS_STANDING)));

    int in_krynn = wildmatch("/d/Ansalon/*",
        file_name(environment(this_player()))) || wildmatch("/d/Krynn/*",
        file_name(environment(this_player())));

    int in_neraka = wildmatch("/d/Ansalon/taman_busuk/neraka/*",
        file_name(environment(this_player())));


    // need to modify the caid taking in to account the white
    // damage harm component, component mod, and the set_caid component.
    int wd_caid = query_white_hit_combat_aid();

    int max_caid = ftoi(PTALON_MAX_CAID) + wd_caid;

    // Base caid is the white damage component of the maximum 
    // caid which should be 100 * 100 / 250 = 40.0
    float modifier = itof(100 * wd_caid / max_caid);


    // Dark warriors have caid in Neraka of 150 (100% of max)
    //                    caid in Krynn of 100  (66.7% of max)
    //                    caid elsewhere of 80  (53.3% of max)
    //                    (average 75 caid outside of Neraka)
    // Unaligned/Dark Lady have caid of 70 in Neraka (46.7% of max)
    //                    caid of 30 in Krynn (20% of max)
    //                    caid of 10 elsewhere (6.7% of max) 
    //                    (average 20 caid outside of Neraka) 


    if (this_player()->query_prop(DARK_WARRIOR_ASPECT))
    {
        if (in_neraka)
            modifier += 100.0 * PTALON_MAX_CAID / itof(max_caid);
        else if (in_krynn)
            modifier += 66.7 * PTALON_MAX_CAID / itof(max_caid);
        else
            modifier += 53.3 * PTALON_MAX_CAID / itof(max_caid);
    } 
    else
    {
        if (in_neraka)
            modifier += 46.7 * PTALON_MAX_CAID / itof(max_caid);
        else if (in_krynn)
            modifier += 20.0 * PTALON_MAX_CAID / itof(max_caid);
        else
            modifier += 6.7 * PTALON_MAX_CAID / itof(max_caid);
    }

    modifier = modifier * pot_standing / 1000.0;
    return modifier;
}
