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

inherit "/d/Genesis/specials/std/spells/blind";
inherit GUILDDIRSPELL + "common";

#define ACTIVE_CURSE "_pot_curse_active"

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int 
query_spell_level(void)
{
    return 8;
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
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

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
    return ({ "eye","gold coin" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    object *target;

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    if(caster->query_prop(DARK_LADY_ASPECT))
      set_spell_time_factor(1.5);
    else
      set_spell_time_factor(2.0);

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

   caster->tell_watcher(QCTNAME(caster) + " throws up " + HIS(caster) + 
      " hands " +
      "and a stream of black fire flows from " + HIS(caster) + " fingers " +
      "towards " +QTPNAME(tar) + " eyes.\n", targets, ({ caster }) + targets);

}

void
hook_use_ingredients(object *ingrs)
{
    int i, j;
    string *arr;
    
    if (IS_LEFTOVER_OBJECT(ingrs[0]))
       i = 0;
    else
       i = 1;
            
    write("A dark flame ignites from within " + LANG_THESHORT(ingrs[i]) +
          ", consuming it in seconds while melting " +
          LANG_THESHORT(ingrs[!i]) + ".\n");
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