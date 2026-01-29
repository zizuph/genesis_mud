/*
 * A recoded version of the Roke healing wand, converted to
 * the new magic system.
 *
 * Coded by Arman 2017.
 *
 * Updated 2019.05.31 by Shanoga
 *   - Added check to see if dragon was zapped on hook_destribe_heal_result
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/heal";

#define DEBUG(x)      find_player("arman")->catch_msg("[RokeWand] " + x + "\n")

/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_heal_spell()
{
    set_spell_name("heal");
    set_spell_desc("Heal - a spell of healing");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_SPELLCRAFT,  20);
    set_spell_form(SS_SPELLCRAFT, 20);
    set_spell_fail("You try to zap your wand but nothing happens.\n");

    set_spell_task(TASK_ROUTINE);
    // 0.75 times the standard cast time for a heal spell 
    set_spell_time_factor(0.75);  

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_combat_aid(35.0);
}

public string *
query_heal_ingredients(object caster)
{
    return ({ });
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    setuid();
    seteuid(getuid());

    return 1;
}

int
filter_tool(object obj)
{
      if (obj->id("wand"))
        return 1;
      else
        return 0;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object *weapon;

    /* Filter out non-staffs */
    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You aren't zap something of you aren't holding the " +
            "wand.\n");
	return 0;
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
    string caster_message, watcher_message, target_message;
    object target = targets[0];
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    if(target->query_real_name() == caster->query_real_name())
    {
        caster_message = "You point the "+wep[0]->short()+" at " +
             "yourself.\n";
        watcher_message = QCTNAME(caster) + " points " + 
              caster->query_possessive() +" "+wep[0]->short()+" at " +
              caster->query_objective()+ "self.\n";

        caster->catch_tell(caster_message);
        tell_room(environment(caster), watcher_message, ({ caster }), caster);

    }
    else
    {
        caster_message = "You point the "+wep[0]->short()+" at " +
            target->query_the_name(caster)+ ".\n";
        target_message = QCTNAME(caster) + " points " + 
            caster->query_possessive() +" "+wep[0]->short()+" at " +
            "you.\n";
        watcher_message = QCTNAME(caster) + " points " + 
            caster->query_possessive() +" "+wep[0]->short()+" at " +
            target->query_the_name(caster)+ ".\n";

        caster->catch_tell(caster_message);
        target->catch_msg(target_message);
        tell_room(environment(caster), watcher_message, ({ caster, target }), 
            caster);

    }

    setuid();
    seteuid(getuid());  
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{

}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    string caster_message, watcher_message, target_message;

    object tar = targets[0];
    int heal = heal_amounts[0];
    object *wep;
    /* Filter out non-staffs and wands */
    wep = filter(caster->query_tool(-1), filter_tool);

    if(tar->query_real_name() == caster->query_real_name())
    {
        caster_message = "You zap yourself with your "+wep[0]->short()+".\n";
        watcher_message = QCTNAME(caster) + " zaps " + 
              caster->query_objective()+ "self with " +
              caster->query_possessive() +" "+wep[0]->short()+".\n";

        caster->catch_tell(caster_message);
        tell_room(environment(caster), watcher_message, ({ caster }), caster);

    }
    else
    {
        caster_message = "You zap "+tar->query_the_name(caster)+ 
            " with your "+wep[0]->short()+".\n";
        target_message = QCTNAME(caster) + " zaps you with " + 
            caster->query_possessive() +" "+wep[0]->short()+".\n";
        watcher_message = QCTNAME(caster) + " zaps " + 
            tar->query_the_name(caster)+ " with " + 
            caster->query_possessive() +" "+wep[0]->short()+".\n";

        caster->catch_tell(caster_message);
        tar->catch_msg(target_message);
        tell_room(environment(caster), watcher_message, ({ caster, tar }), 
            caster);

    }
    
    if (MASTER_OB(tar) == "/d/Khalakhor/inisi/roke/npc/bluedragon")
    {
        tar->notify_been_zapped(wep[0]);
    }
    else
    {
        tar->catch_tell("You feel better.\n");
        tell_room(environment(caster), QCTNAME(tar) + " looks better.\n",
            ({ tar }), caster);

        // DEBUG("Heal amount: " +heal+ ".");
    }
}

/*
 * Function:    hook_insufficient_skill
 * Description: This gets called when the player doesn't have the minimum
 *              skill requirements to cast the spell.
 */

public varargs void
hook_insufficient_skill(object caster, int * needed_skills)
{
    string sMessage = "You do not have the required skills to use this "
        + "wand. You will need more training in spellcraft.\n";

    caster->catch_tell(sMessage);
}