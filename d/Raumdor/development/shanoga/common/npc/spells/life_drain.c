/*
 * life_drain.c
 *
 * Life Drain spell used by lich boss NPC designed for the Raumdor forest.
 * The spell does death damage and is reduced by death resistance. All of
 * the damage is done at the point of impact. Three times the amount of
 * damage done is returned to the caster as a heal. The illusion copies
 * are also healed to help hide what is an illusion and what is not.
 *
 * This spell is modeled after the standard harm spell located at
 * /d/Genesis/specials/std/spells/harm.c
 *
 * Used By: /d/Raumdor/common/npc/lich.c
 *
 * Written by Shanoga under Liege Malus. Updated 2018.03.21
 */

#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

// Prototypes
public void resolve_harm_spell(object caster, object *targets, int *resist,
  int result);

/*
 * Function:    config_harm_spell
 * Description: Configuration function for the harm spell.
 */
public void
config_harm_spell()
{
    set_spell_name("life_drain");
    set_spell_desc("drain life of single enemy");
    set_spell_target(spell_target_one_present_enemy);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(150.0);
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_DEATH));
    set_spell_mana_factor(0.25);
    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(1.0);
    set_spell_ingredients(query_harm_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_ABJURATION, 40);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
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
          "least superior veteran to cast this spell.\n");
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
    caster_message = "You begin to murmur a dark incantation " +
      "to invoke life draining magic!\n";
    watcher_message =
      QCTNAME(caster) + " begins to murmur some dark incantation.\n";
    caster->catch_vbfc(caster_message);
    tell_room(E(caster), watcher_message, caster);
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
    object target = targets[0];
    string caster_message, target_message, watcher_message;
    caster_message =
      "You focus your gaze on " + QTNAME(target) + " and incant louder.\n";
    target_message = QCTNAME(caster) + " focuses " + HIS(caster) + " gaze " +
      "on you as the incantation grows louder.\n";
    watcher_message = QCTNAME(caster) + " focuses " + HIS(caster) + " gaze " +
      "on " + QTNAME(target) + " as the incantation grows louder.\n";
    caster->catch_vbfc(caster_message);
    target->catch_vbfc(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
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
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    caster->heal_hp(2 * result[3]);
    caster->heal_copies(2 * result[3]);
    if (phurt < 0)
    {
        watcher_message = target_message = QCTNAME(caster) + " ends " +
          HIS(caster) + " incantation, without any discernable effect.";
    }
    else
    {
        switch (phurt)
        {
        case 0:
            target_message = "On the final word of " + QTNAME(caster) +
              "'s incantation, you feel a tug at your heart as if with an " +
              "invisible string, but you feel unharmed.\n";
            caster_message =  QCTNAME(target) + " twitches slightly as you " +
              "end your incantation.\n";
            watcher_message = QCTNAME(target) + " twitches slightly as " +
              QTNAME(caster) + " ends " + HIS(caster) + " incantation.\n";
            break;
        case 1..10:
            target_message = "You feel an acute pain in your " + hitloc_desc +
              " and feel drained.\n ";
            caster_message = QCTNAME(target) + " winces in pain.\n";
            watcher_message = caster_message;
            break;
        case 11..20:
            target_message = "There is a sharp pain in your " + hitloc_desc +
              " and you feel " + QTNAME(caster) + " siphoning the life out " +
              "of you!\n";
            caster_message = QCTNAME(target) + " recoils in pain!\n";
            watcher_message = caster_message;
            break;
        case 21..30:
            target_message = "You feel as though " + QTNAME(caster) + 
              " is crushing your " + hitloc_desc + " between its bony " +
              "hands and you tremble in pain.\n" +
              QCTNAME(caster) + " cackles with satisfaction.\n";
            caster_message = QCTNAME(target) + " trembles in pain.\n" +
              QCTNAME(caster) + " cackles with satisfaction.\n";
            watcher_message = caster_message;
            break;
        case 31..40:
            target_message = "Your knees buckle as your soul feels gripped " +
              "by magical chains. You feel as though life itself is being " +
              "drained from you.\n" +
              QCTNAME(caster) + " cackles with pleasure.\n";
            caster_message = QCTNAME(target) + "'s knees buckle in pain.\n" +
              QCTNAME(caster) + " cackles with pleasure.\n";
            watcher_message = caster_message;
            break;
        default:
            target_message = "You stumble and fall to your knees from " +
              "excruciating pain as a dark energy seems to tear you out of " +
              "your own body.\n" +
              QCTNAME(caster) + " shrieks with laughter.\n";
            caster_message = QCTNAME(target) + " stumbles and falls to " +
              HIS(target) + " his knees, clearly in excruciating pain.\n" +
              QCTNAME(caster) + " shrieks with laughter.\n";
            watcher_message = caster_message;
            break;
        }
    }
    caster->catch_vbfc(caster_message + "You drain " + phurt + " life.\n");
    target->catch_vbfc(target_message);
    target->tell_watcher(watcher_message, target, ({ target, caster }));
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their spell again.
 */
public void
hook_special_complete()
{
    write("Life drain ready.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their spell.
 */
public void
hook_special_in_cooldown()
{
    write("Life drain on cooldown.\n");
}

/*
 * Function:    hook_already_active
 * Description: Override this to print out the message players will see
 *              when they are already casting the spell.
 */
public void
hook_already_active(object ability)
{
    write("Life drain already casting.\n");
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
