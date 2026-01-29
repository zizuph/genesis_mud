/*
 * plague_swarm.c
 *
 * Plague swarm spell used by lich boss NPC designed for the Raumdor forest.
 * The spell does minimal initial damage but also applies additional damage
 * over a short duration. The duration damage is significantly greater than
 * the damage applied on hit. If an illusion casts the spell, then the initial
 * damage is reduced to 0 via the spell combat aid and the poison/plague is
 * not applied.
 *
 * This spell is modeled after the standard harm spell located at
 * /d/Genesis/specials/std/spells/harm.c
 *
 * Used By: /d/Raumdor/common/npc/lich.c
 *
 * Written by Shanoga under Liege Malus. Updated 2018.03.21
 */

#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <poison_types.h>
#include "defs.h"

#define PLAGUE_EFFECT   "/d/Raumdor/development/shanoga/common/spell/plague_effect.c"

inherit "/d/Genesis/specials/std/spells/massharm";

object poison;

// Prototypes
public void resolve_harm_spell(object caster, object *targets, int *resist,
  int result);

/*
 * Function:    config_massharm_spell
 * Description: Configuration function for the mass harm spell.
 */
public void
config_massharm_spell()
{
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(75.0);
    set_spell_name("plague_swarm");
    set_spell_desc("minor immediate and duration damage to all enemies");
    set_spell_target(spell_target_present_enemies);    
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_DEATH));
    set_spell_mana_factor(0.25);
    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(1.0);
    set_spell_ingredients(query_massharm_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_restrict_targets(5);
    set_spell_target_limit(3);
}

/*
 * Function:    query_massharm_ingredients
 * Description: This function defines what components are required for
 *              this massharm spell.
 */
public string *
query_massharm_ingredients(object caster)
{
    return ({  });
}

/*
 * Function:    check_valid_action
 * Description: Place restrictions on whether this spell can be used
 *              by the player/living.
 */
public int 
check_valid_action(object caster, mixed *targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_skill(SS_SPELLCRAFT) < 80)
    {
        caster->catch_vbfc("You need to be trained in spellcraft to at " +
          "least superior professional to cast this spell.\n");
        return 0;
    }
  
    return 1;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be learned
 *              by the player/living.
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
        return 1;
    }
    
    return 1;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed *targets, string arg)
{
    string caster_message, watcher_message;
    caster_message = "You extend your hands toward your enemies, " +
      "skeletal fingers splayed, and a faint droning sound begins.\n";
    watcher_message = QCTNAME(caster) + " extends its hands outward, " +
      "skeletal fingers splayed, and a faint droning sound begins.\n";
    caster->catch_vbfc(caster_message);
    tell_room(E(caster), watcher_message, ({ caster }), caster);
    setuid();
    seteuid(getuid());
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
{
    string caster_message, target_message, watcher_message;
    caster_message = "The drone grows louder as a swarm of carrion insects " +
      "enter the battlefield to feast on the flesh of your enemies.\n";
    target_message = "The drone grows louder as a swarm of carrion insects " +
      "surround you, feasting for your flesh.\n";
    watcher_message = "The drone grows louder as a swarm of carrion insects " +
      "fills the area, feasting for flesh.\n";
    caster->catch_vbfc(caster_message);
    targets->catch_vbfc(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);
}

/*
 * Function name: do_harm_damage
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public mixed *
do_massharm_damage(object caster, object target, int pen)
{
    if (caster->query_is_illusion())
    {
        pen = 0;
    }
    return ::do_massharm_damage(caster, target, pen);
}

/*
 * Function name: resolve_harm_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_harm_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    if (caster->query_is_illusion())
    {
        target_message = "The swarm of insects passes right through you.\n";
        caster_message = "The swarm of insects passes right through your " +
          "enemies.\n";
    }
    else
    {
        if (phurt > 0)
        {
            poison = clone_object(PLAGUE_EFFECT);
            poison->move(target);
            poison->start_poison(caster);

        }
        
        if (phurt < 0)
        {
            target_message = "The swarm of insects move on as quickly as " +
              "they arrived, leaving only the smell of death behind.\n";
            caster_message = target_message;
        }
        else
        {   
            switch (phurt)
            {
            case 0:
                target_message = "As the swarm passes by you, several of " +
                  "the insects land on your " + hitloc_desc + ", but you " +
                  "are able to brush them off before they can bite you.\n";
                caster_message = "As the swarm passes by " + QTNAME(target) +
                  ", several of the insects land on " + HIS(target) + " " +
                  hitloc_desc + ", but " + HE(target) + " is able to brush " +
                  "them off before they can bite " + HIM(target) + ".\n";
                break;
                
            case 1..10:
                target_message = "While the insect swarm buzzes all around " +
                  "you, your skin is pricked by their tiny mandibles.\n";
                caster_message = "While the insect swarm buzzes all around " +
                  QTNAME(target) +", " + HE(target) + " is pricked by the " +
                  "insects' tiny mandibles.\n";
                break;
                
            case 11..20:
                target_message = "You can feel your " + hitloc_desc +
                  " beginning to rot from the bites of the " +
                  "plague-carrying swarm.\n";
                caster_message = "You can see " + QTNAME(target) + "'s  " +
                  hitloc_desc + " beginning to rot from the bites " +
                  "of the plague-carrying swarm.\n";
                break;
                
            case 21..30:
                target_message = "Several of the insects bite deeply into " +
                  "your " + hitloc_desc + ", infecting you with necropathy.\n";
                caster_message = "Several of your insects bite deeply into " +
                  QTNAME(target) + "'s " + hitloc_desc + ", infecting " +
                  HIM(target) + " with necropathy.\n";
                break;
                
            default:
                target_message = "The swarm of insects claw and bite under " +
                  "every part of your body, filling you with searing pain " +
                  "and a toxic plague.\n";
                caster_message = "The swarm of insects claw and bite " +
                  "under every part of " + QTNAME(target) + ", filling " +
                  HIM(target) + " with searing pain and a toxic plague.\n";
                break;            
            }
        }
    }
    caster->catch_vbfc(caster_message);
    target->catch_vbfc(target_message);
}

/*
 * Function:    hook_attack_object
 * Description: Masking this so that you won't see many attack messages
 *              when it would attack multiple targets, if already attacking.
 */
public void
hook_attack_object(object ob)
{
    if (IN_ARRAY(ob, this_player()->query_enemy(-1)))
    {
        return;
    }
    ::hook_attack_object(ob);
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their spell again.
 */
public void
hook_special_complete()
{
    write("Plague swarm ready.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their spell.
 */
public void
hook_special_in_cooldown()
{
    write("Plague swarm on cooldown.\n");
}

/*
 * Function:    hook_already_active
 * Description: Override this to print out the message players will see
 *              when they are already casting the spell.
 */
public void
hook_already_active(object ability)
{
    write("Plague swarm already casting.\n");
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used. 
 */
public void
list_spells()
{
    write(sprintf("%-15s %s\n", query_spell_name(), ::query_spell_desc()));
}