/*
 * ice_storm.c
 *
 * Ice Storm spell used by lich boss NPC designed for the Raumdor forest.
 * The spell does water damage and is reduced by cold resistance. All of
 * the damage is done at the point of impact.
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
#include "defs.h"

inherit "/w/shanoga/test/spell/massharm";

static mapping  enemies = ([]);

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
    set_spell_name("ice_storm");
    set_spell_desc("barrage of ice on all enemies");
    set_spell_target(spell_target_present_enemies);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(90.0);
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_COLD));
    set_spell_mana_factor(0.25);
    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(1.0);
    set_spell_ingredients(query_harm_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    set_spell_element(SS_ELEMENT_WATER, 40);
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
    caster_message = "You extend both of your arms to the sky and a dark " +
      "cloud begins to gather above your enemies.\n";
    watcher_message = QCTNAME(caster) + " extends both of its arms to " +
      "the sky and a dark cloud begins to gather in the air.\n";
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
    caster_message = "Before they can react, frozen shards of ice " +
      "begin to rain down upon them!\n";
    target_message = "Before you can react, frozen shards of ice " +
      "begin to rain down upon you!\n";
    watcher_message = "Frozen shards of ice begin to rain down all " +
      "around you!\n";
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
    find_player("shanoga")->catch_vbfc("\n\nICE STORM DAMAGE % : " + phurt + "\n\n");
    string hitloc_desc = result[1];
    if (caster->query_is_illusion())
    {
        target_message = "The frozen debris crashes through you.\n";
        caster_message = "The frozen debris crashes through your enemies.\n";
    }
    else
    {
        if (phurt < 0)
        {
            target_message = "The barrage of ice crashes around you " +
              "harmlessly.\n";
            caster_message = "The barrage of ice crashes around " + 
              QTNAME(target) + " harmlessly.\n";
        }
        else
        {   
            switch (phurt)
            {
            case 0:
                target_message = "Ice shards collide with your " +
                  hitloc_desc + ", but ricochet ineffectively.\n";
                caster_message = "Ice shards collide with " +
                  QTNAME(target) + "'s " + hitloc_desc + ", but ricochet " +
                  "ineffectively.\n";
                break;
                
            case 1..10:
                target_message = "The falling shards rain onto your " +
                  hitloc_desc + " and you feel a stinging chill.\n";
                caster_message = "The falling shards rain onto " +
                  QTNAME(target) + "'s " + hitloc_desc +  ", causing a " +
                  "stinging chill.\n";
                break;
                
            case 11..20:
                target_message = "You are scratched and bruised by the " +
				  "storm.\n";
                caster_message = "Your enemies are scratched and bruised " +
                  "by the storm.\n";
                break;
                
            case 21..30:
                target_message = "You are battered and cut by the barrage!\n";
                caster_message = "Your enemies are battered and cut by the " +
                  "barrage.\n";
                break;

            case 31..40:
                target_message = "You can feel the ice slicing through the " +
                  "skin of your " + hitloc_desc + ", freezing you from " +
                  "within!\n";
                caster_message = "You see the ice slicing through the skin " +
                  "of your enemies, freezing them from within!\n";
                break;

            case 41..50:
                target_message = "You have icicles hanging from your " +
                  "bleeding and frostbitten " + hitloc_desc + "!\n";
                caster_message = "You can see icicles forming on your " +
				  "bleeding and frostbitten enemies!\n";
                break;
                
            default:
                target_message = "You can hardly move due to the furious " +
                  "onslaught and your frozen muscles!\n";
                caster_message = "You can see your enemies turning into " +
				  "statues under your frozen onslaught!\n";
                break;            
            }
        }
    }
        
    caster->catch_vbfc(caster_message);
    target->catch_vbfc(target_message);
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their spell again.
 */
public void
hook_special_complete()
{
    write("Ice storm ready.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their spell.
 */
public void
hook_special_in_cooldown()
{
    write("Ice storm on cooldown.\n");
}

/*
 * Function:    hook_already_active
 * Description: Override this to print out the message players will see
 *              when they are already casting the spell.
 */
public void
hook_already_active(object ability)
{
    write("Ice storm already casting.\n");
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