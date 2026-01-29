/*
 * pPain
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "stun";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include <language.h>

inherit GUILDDIRSPELL + "common";

#define ACTIVE_CURSE "_pot_curse_active"
#define BLIND_CURSE "_pot_blind_curse"


// Use up the slime one out of six casts.  Matches the
// dagger shard creation of 6 per dagger.
#define SLIME_KEEP_PERCENTAGE   (83)   


object ppain_target;

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 12;
}

/*
 * Function:    config_stun_spell
 * Description: Config function for stun spells. Redefine this in your
 *              own stun spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_stun_spell()
{
    set_spell_name("ppain");
    set_spell_desc("Paralyze your enemy with pain");

    set_spell_element(SS_ELEMENT_LIFE, 77);
    set_spell_form(SS_FORM_TRANSMUTATION, 77);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);


    // 1+ herb per cast
    set_spell_component_factor(COMPONENT_AID_LOW);

    set_spell_combat_aid(45.0);
    set_spell_object(PAIN_OBJ);

}

/*
 * Function:    query_stun_ingredients
 * Description: This function defines what components are required for
 *              this stun spell.
 */
public string *
query_stun_ingredients(object caster)
{
    return ({"green slime","heart","_pot_knife_shard"});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{

    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    object *target;

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Warrior, you " +
           "cannot call upon this curse.\n");
        return 0;
    }

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun())))
    {   
        if (target[0]->query_pot_active())
        {
            caster->catch_tell("You notice " + COMPOSITE_LIVE(targets) +
            " is already paralyzed with excrutiating pain.\n");
            find_player("arman")->catch_msg("[PoT] test\n");
            return 0;
        }
    }

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_pot_stun())))
    {   
        if (target[0]->query_pot_cooldown())
        {
            caster->catch_tell("It is too soon to call down the wrath of " +
             "Takhisis again! You risk drawing the ire of the goddess by " +
             "beseeching her too frequently!\n");
            return 0;
        }
    }

    if(caster->query_prop(DARK_LADY_ASPECT))
    {
       if (targets[0]->query_prop(ACTIVE_CURSE))
       {
        caster->catch_tell("A curse has already been cast " +
	    "upon "+ COMPOSITE_LIVE(targets) +". While aspected to " +
            "the Dark Lady you can only beseech the wrath " +
            "of Takhisis with a single curse at a time!\n");
        return 0;
       }
       if (targets[0]->query_prop(BLIND_CURSE))
       {
         caster->catch_tell("While under the aspect of the Dark Lady " +
           "you cannot summon the wrath of Takhisis on a foe affected " +
           "by pblind.\n");
        return 0;
       }
    }

    return 1;
}

/*
 * Function:    hook_describe_cast_stun
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_stun(object caster, object * targets)
{
    object target = targets[0];

    caster->catch_tell("You point at " + COMPOSITE_LIVE(targets) + " and say: " +
        "Feel the wrath of the Dark Queen!\n");
    target->catch_msg(QCTNAME(caster) + " points at you, saying: Feel the " +
        "wrath of the Dark Queen!\n");
    caster->tell_watcher(QCTNAME(caster) + " points at " +QTNAME(target)+
        " and says: Feel the wrath of the Dark Queen!\n", targets, 
        ({ caster }) + targets);
}

/*
 * Function:    hook_target_stun_resisted
 * Description: Called to show the messages of the targets that were not
 *              stunned because they resisted the spell.
 */
public void
hook_target_stun_resisted(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("Takhisis doesn't answer your call to paralyze " + 
       COMPOSITE_LIVE(targets)+ " with pain.\n");
    targets->catch_tell("You resist the wrath of the dark goddess " +
       "Takhisis.\n"); 
}


/*
 * Function:    hook_target_stun_succeeded
 * Description: Called to show the messages of the targets that were
 *              affected by the stun. Part of the stun messages
 *              will also be described by the stun object itself. Note
 *              that it's entirely possible the stun spell may hit,
 *              but because of a cooldown period, the stun may not
 *              actually have any effect.
 */
public void
hook_target_stun_succeeded(object caster, object * targets)
{
    if (!sizeof(targets))
        return;

    object tar = targets[0];
    caster->catch_tell(C(HE(tar))+" cries out as a wave of pain "+
	"sears through "+HIS(tar)+" body.\n");
    tar->catch_tell("You cry out as a wave of pain sears through your body.\n");
    tell_room(environment(tar), QCTNAME(tar) + " cries out in pain.\n", 
        ({caster, tar}), tar);

}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the caster when
 *                the targets has disappeared during the prepartion of the
 *                spell.
 * Returns:       The message to print
 */
public void
hook_targets_gone()
{
    // For mounted knights charging, this message can be removed
    if(objectp(ppain_target) && ppain_target->query_prop("_kcharge_preparing"))
      return;

    write("Nobody here to cast the spell on!\n");
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_no_attack_fail(mixed reason)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else if(objectp(ppain_target) && ppain_target->query_prop("_kcharge_preparing"))
    {
        write("Your target has moved out of range of your spell.\n");
    } 
    else
    {
        write("You feel a divine force protecting this being, your " +
               "attack fails.\n");
    }
}

public void
hook_use_ingredients(object *ingrs)
{
    int i, j, k;

    if (ingrs[0]->is_knife_shard())
    {
        i = 0;

        if (ingrs[1]->query_herbname() == "green slime") 
        {
          j = 1;
          k = 2;
        }
        else 
        {
          j = 2;
          k = 1;
        } 
    }

    if (ingrs[1]->is_knife_shard())
    {
        i = 1;

        if (ingrs[0]->query_herbname() == "green slime") 
        {
          j = 0;
          k = 2;
        }
        else 
        {
          j = 2;
          k = 0;
        } 
    } 

    if (ingrs[2]->is_knife_shard())
    {
        i = 2;

        if (ingrs[0]->query_herbname() == "green slime") 
        {
          j = 0;
          k = 1;
        }
        else 
        {
          j = 1;
          k = 0;
        } 
    } 

    string heart_consumed1 = ", making it burst into flames";
    string heart_consumed2 = " and combusting";

    if (random(100) < SLIME_KEEP_PERCENTAGE)
    {
        ingrs[j]->add_prop("_savable_from_consumption", 1);
        heart_consumed1 = "";
        heart_consumed2 = "";
    }


    if (ingrs[k]->query_leftover_powder())
       write("You stab " + LANG_THESHORT(ingrs[i]) + " into " +
          LANG_THESHORT(ingrs[k]) + ", its ichor dripping on to " +
          LANG_THESHORT(ingrs[j]) + heart_consumed2 +", consuming the " +
          "powder and blade.\n"); 
    else
       write("As you stick " + LANG_THESHORT(ingrs[i]) + " into and " +
          "through the heart, you let the blood drip onto " +
          LANG_THESHORT(ingrs[j]) + heart_consumed1 + 
          ", consuming the heart and blade.\n");
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
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public nomask float
query_spell_combat_aid_modifier()
{
    float modifier = 100.0;
    
    if (!this_player()->query_prop(DARK_LADY_ASPECT))
        modifier = 45.0;

    if(BETA_CAID_MOD)
        modifier = modifier * 9.0 / 10.0;

    return modifier;
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