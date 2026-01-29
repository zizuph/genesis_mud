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

inherit "/d/Genesis/specials/std/spells/mass_harm";

object poison;

// Prototypes
public void plagueswarm_desc_cast(object caster, object target);
public void resolve_harm_spell(object caster, object *targets, int *resist,
  int result);
public void swarm_desc_damage(object caster, object target, mixed * result);
public void plagueswarm_desc_damage(object caster, object target, int phurt,
  string hitloc_desc);

/*
 * Function:    config_massharm_spell
 * Description: Configuration function for the mass harm spell.
 */
public void
config_massharm_spell()
{
    set_spell_name("plague_swarm");
    set_spell_desc("minor immediate and duration damage to all enemies");
    set_spell_target(spell_target_present_enemies);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(75.0);
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_DEATH));
    set_spell_mana_factor(0.25);
    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(1.0);
    set_spell_ingredients(query_massharm_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
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
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_skill(SS_SPELLCRAFT) < 80)
    {
        caster->catch_tell("You need to be trained in spellcraft to at " +
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
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message;
    caster_message = "You are preparing plague swarm!\n";
    caster->catch_tell(caster_message);
    setuid();
    seteuid(getuid());  
}

/*
 * Function name: plagueswarm_desc_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
plagueswarm_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    caster_message = "You extend your hands toward your enemies, " +
      "skeletal fingers splayed. A droning sound begins faintly, " +
      "but growing louder as a swarm of carrion insects enter the " +
      "battlefield to feast on the flesh of your enemies.\n";
    /*
    watcher_message = QCTNAME(caster) + " extends its hands toward you, " +
      "skeletal fingers splayed. A droning sound begins faintly, but " +
      "growing louder as a swarm of carrion insects surround you, " +
      "feasting for your flesh.\n";
    */
    target_message = QCTNAME(caster) + " extends its hands toward you, " +
      "skeletal fingers splayed. A droning sound begins faintly, but " +
      "growing louder as a swarm of carrion insects surround you, " +
      "feasting for your flesh.\n";
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));
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
    foreach (object target : targets)
    {
        plagueswarm_desc_cast(caster, target);  
    }
}

/*
 * Function name: do_harm_damage
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public mixed *
do_harm_damage(object caster, object target, int pen)
{
    if (caster->query_is_illusion())
    {
        pen = 0;
    }
    return ::do_harm_damage(caster, target, pen);
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
 * Function name: swarm_desc_damage
 * Description:   Describe the damage of the spell
 * Arguments:     object caster   - the caster
 *                object target   - the target
 *                mixed * result  - an array of:
 *                  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
 */
public void
swarm_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    plagueswarm_desc_damage(caster, target, phurt, hitloc_desc);
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
    swarm_desc_damage(caster, target, result);
}

/*
 * Function name: plagueswarm_desc_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                int phurt - percentage of target's current health lost
 *                string hitloc_desc - target's hitloc that takes damage
 */
public void
plagueswarm_desc_damage(object caster, object target, int phurt,
    string hitloc_desc)
{
    string target_message, watcher_message;
    if (caster->query_is_illusion())
    {
        target_message = "The swarm of insects passes right through you.\n";
        watcher_message = "The swarm of insects passes right through your " +
          "enemies.\n";
    }
    else
    {
        if (phurt > 0)
        {
            // Temporary Path
            poison = clone_object("/d/Raumdor/development/shanoga/common/npc/spells/plague_effect.c");
            poison->move(target);
            poison->start_poison(caster);

        }
        
        if (phurt < 0)
        {
            target_message = "The swarm of insects move on as quickly as " +
              "they arrived, leaving only the smell of death behind.\n";
            watcher_message = "The swarm of insects move on as quickly as " +
              "they arrived, leaving only the smell of death behind.\n";
        }
        else
        {   
            switch (phurt)
            {
            case 0:
                target_message = "As the swarm passes by you, several of " +
                  "the insects land on your " + hitloc_desc + ", but you " +
                  "are able to brush them off before they can bite you.\n";
                break;
                
            case 1..10:
                target_message = "While the insect swarm buzzes all around " +
                  "you, your skin is pricked by their tiny mandables.\n";
                watcher_message = "While the insect swarm buzzes all around " +
                  "your enemies, they are pricked by the insects' tiny " +
                  "mandables.\n";
                break;
                
            case 11..20:
                target_message = "You can feel the skin on your " +
                  hitloc_desc + " beginning to rot from the bites of the " +
                  "plague-carrying swarm.\n";
                watcher_message = "You can see the skin on your enemies " +
                  "beginning to rot from the bites of the plague-carrying " +
                  "swarm.\n";
                break;
                
            case 21..30:
                target_message = "Several of the insects bite deeply into " +
                  "the skin of your " + hitloc_desc + ", killing the skin " +
                  "and infecting your blood with necropathy.\n";
                watcher_message = "Several of your insects bite deeply into " +
                  "the skin of your enemies, killing the skin and " +
                  "infecting their blood with necropathy.\n";
                break;
                
            default:
                target_message = "The swarm of insects claw and bite under " +
                  "every part of your body, ravaging your skin and " +
                  "flooding your blood with a toxic plague.\n";
                watcher_message = "The swarm of insects claw and bite " +
                  "under every part of your enemies, ravaging their skin " +
                  "and flooding their blood with a toxic plague.\n";
                break;            
            }
        }
    }
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
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