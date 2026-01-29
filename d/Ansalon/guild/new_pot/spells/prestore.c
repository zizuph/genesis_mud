/*
 * pRestore
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include <poison_types.h>
#include <composite.h>
#include <language.h>
#include <wa_types.h>

#include "../guild.h"
#include "../spells.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "cleanse";
inherit GUILDDIRSPELL + "common";

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 8;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You bow your head in prayer.\n");
    tell_room(environment(caster), QCTNAME(caster) + " bows " + HIS(caster) + 
        " head in prayer.\n", ({ caster }), caster);
    set_this_player(old_tp);
}

/*
 * Function:    resolve_cleanse_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_cleanse_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    config_cleanse_spell
 * Description: Config function for cleanse spells. Redefine this in your
 *              own cleanse spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_cleanse_spell()
{
    set_spell_name("prestore");
    set_spell_desc("prayer of poison cleansing");

    set_spell_element(SS_ELEMENT_LIFE, 55);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);

}

/*
 * Function:    query_cleanse_ingredients
 * Description: This function defines what components are required for
 *              this cleanse spell.
 */
public string *
query_cleanse_ingredients(object caster)
{
    return ({"rib", "_leftover_pearl_dust"});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Warrior, you cannot " +
           "request this prayer of cleansing.\n");
        return 0;
    }

    return 1;
}

public void
hook_describe_cleanse_cast(object caster, object * targets)
{
    object tar = targets[0];

    // casting on good aligned targets results in a standing adjustment.

    if (tar->query_alignment() > 100)
    {
        caster->catch_tell("You find it more difficult cleansing poisons from " +
            "someone not dark of heart, and feel less in touch with Takhisis.\n");
        caster->adjust_standing(RND_RANGE(-70, 20));
    }

    if (tar == caster)
    {
        caster->catch_tell("You call upon dark forces to draw poison from your body.\n");
        tell_room(environment(caster), QCTNAME(caster) +
	    " calls upon dark forces to draw poison from " +HIS(caster)+ " body.\n", targets);
    }
    else
    {
        caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " shivers as you attempt to cleanse " +HIM(tar)+ " of poisons.\n");
        tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you shiver as " + HE(caster)+
	    " attempts to cleanse you of poisons.\n");
        tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " shivers as " + HE(tar) + " is cleansed of poisons.\n",
	    ({ caster, tar }), caster);
    }

}

public void
hook_all_poisons_cleansed(object caster, object target)
{
    if(caster == target)
       caster->catch_tell("You successfully cleanse all poisons from yourself.\n");
    else
    {
      caster->catch_tell("You successfully cleanse all poisons from " +COMPOSITE_LIVE(target)+".\n");
      target->catch_msg(QCTNAME(caster) + " cures all of your poisons.\n");
    }
}

public void
hook_some_poisons_cleansed(object caster, object target)
{
    if(caster == target)
      caster->catch_tell("You successfully cleanse some poisons from yourself, however " +
        "some still remain.\n");
    else
    {
      caster->catch_tell("You manage to cleanse some poisons from " +COMPOSITE_LIVE(target)+
        ", but still some remain.\n");
      target->catch_msg(QCTNAME(caster) + " cures some of your poisons, but "
        + "some still remain.\n");
    }
}

public void
hook_use_ingredients(object *ingrs)
{
    int i;

    if (IS_LEFTOVER_OBJECT(ingrs[0]))
        i = 0;
    else
        i = 1;
            
    write("You mix " + LANG_THESHORT(ingrs[i]) + " with the " +
          LANG_THESHORT(ingrs[!i]) + ", forming a black ichor " +
          "which pours from your hands.\n");
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
            
        if (actor->query_skill(PS_STANDING) < -900)
            return convert_task_to_hit(TASK_FORMIDABLE);
        
        // harder to cast on when in poor standings
        if (actor->query_skill(PS_STANDING) < -300 ||
           (living(target) && target->query_alignment() > 101))
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
