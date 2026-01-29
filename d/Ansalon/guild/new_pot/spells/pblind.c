/*
 * pBlind
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include <language.h>
#include <wa_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "blind";
inherit GUILDDIRSPELL + "common";

#define ACTIVE_CURSE "_pot_curse_active"

#define LEFTOVER_KEEP_PERCENTAGE 50


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int 
query_spell_level(void)
{
    return 8;
}

public float
dark_lady_factor()
{
    if(this_player()->query_prop(DARK_LADY_ASPECT))
      return 1.0;
    else
      return 1.5;
}

/*
 * Function:    config_blind_spell
 * Description: Config function for blind spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blind_spell()
{
    set_spell_name("pblind");
    set_spell_desc("Blind an enemy with unholy fire");

    set_spell_element(SS_ELEMENT_AIR,   40);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    
    // 30 CAID for Lady aspect, 20 for the others, applied by modifier.
    set_spell_combat_aid(30);

    // easily obtained components.
    set_spell_component_factor(COMPONENT_AID_LOW);

    set_spell_time_factor(dark_lady_factor);
    // Set the effect object filename
    set_spell_object(GUILDDIRSPELL + "obj/pblind");

}

/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind vision spell.
 */
public string *
query_blind_ingredients(object caster)
{
    return ({ "_leftover_eye_powder","gold coin" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    object *target;

    if (caster->query_prop(DARK_LADY_ASPECT) &&
        targets[0]->query_prop(ACTIVE_CURSE))
    {
            caster->catch_tell("While under the aspect of the Dark Lady " +
             "you cannot blind a foe affected by pcurse.\n");
            return 0;
    }

    if (caster->query_prop(DARK_LADY_ASPECT) &&
        (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun()))))
    {
        if(target[0]->query_pot_cooldown())
            return 1;
   
        caster->catch_tell("While under the aspect of the Dark Lady " +
           "you cannot blind a foe affected by ppain.\n");
        return 0;
    }

    return 1;
}

/*
 * Function:    resolve_blind_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_blind_spell(object caster, mixed * targets, int * resist, int result)
{
    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your prayer.\n");
    target->catch_msg("You resisted " + QTNAME(caster)+"'s prayer.\n");
}

public void
hook_describe_blind(object caster, mixed * targets, int result)
{
   object tar = targets[0];

   caster->catch_msg("You throw up your" +
	  " hands and a stream of black fire flows from your" +
	  " fingers towards " +QTPNAME(tar)+ " eyes. The fire enters " +
	  HIS(tar)+ " eyes and engulfs them!\n");

   tar->catch_msg(caster->query_The_name(tar)+" throws up "+
	  HIS(caster)+" hands and a stream of black fire flows from "+
	  HIS(caster)+" fingers towards your eyes, engulfing them.\n");

   caster->query_combat_object()->
       tell_watcher(QCTNAME(caster) + " throws up " + HIS(caster) + 
      " hands " +
      "and a stream of black fire flows from " + HIS(caster) + " fingers " +
      "towards " +QTPNAME(tar) + " eyes.\n", targets, ({ caster }) + targets);

}

void
hook_use_ingredients(object *ingrs)
{
    object * consumed = ({ });
    
    object coin;    
    object leftover;
    
    foreach(object ob : ingrs)
    {
        
        if (IS_LEFTOVER_OBJECT(ob))
        {
            if (random(100) <LEFTOVER_KEEP_PERCENTAGE)
            {
                ob->add_prop("_savable_from_consumption", 1);
            }
            else
            {
                leftover = ob;
                consumed += ({ ob });
            }
        }
        else
        {
            coin = ob;
        }
    }
    if (leftover)
    {
        write("A dark flame ignites from within " + LANG_THESHORT(leftover) +
          ", consuming it in seconds while melting " +
          LANG_THESHORT(coin) + ".\n");
    }
    else
    {
        write("A dark flame ignites from within " + LANG_THESHORT(coin) +
          ", melting it in seconds.\n");
    }
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

int keep_leftover;

int query_keep_leftover()
{
    return keep_leftover;
}

int set_keep_leftover(int i)
{
    keep_leftover = i;
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

public float query_combat_aid_modifier()
{
    if(this_player()->query_prop(DARK_LADY_ASPECT))
        return 100.0;
    return 66.7;
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
