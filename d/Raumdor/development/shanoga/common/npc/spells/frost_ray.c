/*
 * Frost Ray spell used by lich boss NPC designed for the Raumdor forest.
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
    set_spell_name("frost_ray");
    set_spell_desc("ice beam to single enemy");
    set_spell_target(spell_target_one_present_enemy);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(125.0);
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_COLD));
    set_spell_mana_factor(0.25);
    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(1.0);
    set_spell_ingredients(query_harm_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
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

    if(caster->query_skill(SS_SPELLCRAFT) < 50)
    {
        caster->catch_vbfc("You need to be trained in spellcraft to at " +
          "least superior journeyman to cast this spell.\n");
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
    caster_message = "You raise your right hand and extend a bony finger.\n";
    watcher_message = QCTNAME(caster) + " raises its right hand and " +
      "extends a bony finger.\n";
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
    caster_message = "A pale blue beam shoots from your finger straight " +
      "toward " + QTNAME(target) + "!\n";
    target_message = "A pale blue beam shoots from " + HIS(caster) +
      " finger straight toward you!\n";
    watcher_message = "A pale blue beam shoots from its finger straight toward " +
      HIM(target) + "!\n";
    caster->catch_vbfc(caster_message);
    target->catch_vbfc(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
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
    if (caster->query_is_illusion())
    {
        target_message = "You are hit in the " + hitloc_desc + ", but " +
          "the icy beam passes right through you, doing nothing.\n";
        watcher_message = "A crackling beam of ice passes right through " + 
          QCTNAME(target) + "'s " + hitloc_desc + ", doing nothing.\n";
    }
    else
    {   
        switch (phurt)
        {
        case 0:
            target_message = "You are hit in the " + hitloc_desc + ", " +
              "but you resist the ray of frost.\n";
            caster_message = "A crackling beam of ice hits " +
              QCTNAME(target) + " in " + HIS(target) +
              " " + hitloc_desc +    ", but " + HE(target) +
              "resists the effects of the ray of frost entirely.\n";
            watcher_message = caster_message;
            break;
        case 1..10:
            target_message = "The ray of frost hits your " + hitloc_desc 
              + " and you feel a slight chill.\n";
            caster_message = "The ray of frost hits " + QTNAME(target) +
              " in the " + hitloc_desc +  ", causing a slight chill.\n";
            watcher_message = caster_message;
            break;
        case 11..20:
            target_message = "You feel a shiver from the beam's icy " +
              "touch.\n";
            caster_message = QCTNAME(target) + " shivers from " +
              "the beam's icy touch.\n";
            watcher_message = caster_message;
            break;
        case 21..30:
            target_message = "The ray of frost explodes into your " +
              hitloc_desc + ", causing your entire being to shiver " +
              "from the cold.\n";
            caster_message = "The ray of frost explodes into "+ 
              QTNAME(target) + "'s " + hitloc_desc + ", causing " +
              HIM(target) + " to shiver violently.\n";
            watcher_message = caster_message;
            break;
        case 31..40:
            if (target->query_prop(LIVE_I_UNDEAD))
            {
                target_message = "The ray of frost slams you in your" +
                  hitloc_desc + ".\n";
                caster_message = "The ray of frost slams " + QTNAME(target) +
                  "'s " + hitloc_desc + ".\n";
                watcher_message = caster_message;
            }
            else
            {
                target_message = "The ray of frost slams you in your" +
                  hitloc_desc + ", causing frostbite.\n";
                caster_message = "The ray of frost slams " + QTNAME(target) +
                  "'s " + hitloc_desc + ", causing frostbite.\n";
                watcher_message = caster_message;
            }
            break;
        default:
            target_message = "The ray of frost pierces straight into " +
              "your " + hitloc_desc + ", freezing you to your core.\n";
            caster_message = "The ray of frost pierces straight into " +
              QTNAME(target) + "'s " + hitloc_desc + ", freezing " +
              HIM(target) + " to " + HIS(target) + " core.\n";
            watcher_message = caster_message;
            break;
        }
    }
    caster->catch_vbfc(caster_message);
    target->catch_vbfc(target_message);
    caster->tell_watcher(watcher_message, caster, target);
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their spell again.
 */
public void
hook_special_complete()
{
    write("Frost ray ready.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their spell.
 */
public void
hook_special_in_cooldown()
{
    write("Frost ray on cooldown.\n");
}

/*
 * Function:    hook_already_active
 * Description: Override this to print out the message players will see
 *              when they are already casting the spell.
 */
public void
hook_already_active(object ability)
{
    write("Frost ray already casting.\n");
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
