/*
 * pTalon
 *
 * Modified to new magic system July 2016 - Arman
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/harm";

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

int used_soul_gem = 0;


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

    set_spell_task(TASK_ROUTINE);

    // 1.5 times the standard cast time for a harm spell 
    set_spell_time_factor(1.5); 
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_combat_aid(70.0);
}

/* 
 * Function:    ignore_spell_ingredients
 * Description: Function that allows a person to ignore spell ingredients
 *              By default, npcs and wizards who have a special property
 *              set will be able to ignore spell ingredients.
 */
public int
ignore_spell_ingredients(object caster)
{
    object gem;

    // DEBUG("ptalon components: can ignore checked.");

    if (!objectp(caster))
    {
        return 0;
    }

    if(used_soul_gem)
        return 1;

    if ((gem = P(MEDALLION_ID, caster)->query_soul_gem()) &&
        gem->query_charge() < 100)
    {
        caster->catch_tell("The " + gem->short() + " doesn't " +
            "have enough energy remaining from captured souls, " +
            "so you resort to your prayer components.\n");

        used_soul_gem = 1;

        // DEBUG("ptalon components: not enough charge checked.");
        return 0;
    }

    if ((gem = P(MEDALLION_ID, caster)->query_soul_gem()) &&
        gem->query_charge() >= 100)
    {
        gem->add_charge(-100);
            
        if (calling_function() != "cast_spell")
            caster->catch_tell("The " + gem->short() + " throbs as you " +
               "draw from the energy of your captured souls.\n");

        used_soul_gem = 1;

        // DEBUG("ptalon components: charge extracted.");
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
    used_soul_gem = 0;

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

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    int in_krynn = wildmatch("/d/Ansalon/*",
        file_name(environment(caster))) || wildmatch("/d/Krynn/*",
        file_name(environment(caster)));
    int in_neraka = wildmatch("/d/Ansalon/taman_busuk/neraka/*",
        file_name(environment(caster)));

    // harder to cast on evil aligned, except in Neraka and on
    // warfare npcs
    if(in_neraka)
	set_spell_task(TASK_ROUTINE);
    else if (targets[0]->id("_warfare_npc_"))
	set_spell_task(TASK_ROUTINE);
    else if (targets[0]->query_alignment() < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (targets[0]->query_alignment() < -300)
	set_spell_task(TASK_HARD);
    else
	set_spell_task(TASK_ROUTINE);

    int pot_standing = min(1000, caster->query_skill(PS_STANDING));
    float c_aid, location_mod;

    if(in_neraka)
      location_mod = 2.0;  
    else if(in_krynn)
      location_mod = 1.5;
    else
      location_mod = 1.0;

    // max combat aid for ptalon Dark Warrior aspect: 
    //      (Neraka / Krynn / elsewhere)
    //        230   /  180  /   130
    // max combat aid for ptalon unaspected / Dark Lady aspect:
    //         90   /  70   /   50  

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
        c_aid = max(30.0, (itof(pot_standing / 10) * location_mod) + 30.0);
    else
        c_aid = max(30.0, (itof(pot_standing / 25) * location_mod) + 10.0);

    if(BETA_CAID_MOD)
        c_aid = c_aid * 0.9;

    set_spell_combat_aid(c_aid);

    // DEBUG("ptalon combat aid: "+ftoi(c_aid)+".");

    return 1;
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
    used_soul_gem = 0;
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
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}