/*
 * Ptell Spell for Priests of Takhisis
 * 
 * This is a spell to allow the priests to send a message over great
 * distance to any specified target.
 *
 * Created by Navarre, March 3rd 2013
 */
#pragma strict_types

// Inherit the global tell far spell.
inherit "/d/Genesis/specials/std/spells/fartell";

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/guild/new_pot/std/generic_functions.c"
#include "/d/Ansalon/common/defs.h"
#include "../defs.h"

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public varargs int
config_fartell_spell()
{
    set_spell_name("ptell");
    set_spell_desc("Talk to someone across a distance");
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);
    set_spell_vocal(1);
    set_spell_visual(0);
    // set_spell_stationary(0); -- Cannot be overridden due to global spell.
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_resist(0);
    set_can_fartell_unmet(1);
    set_spell_task(TASK_EASY);
    set_spell_time_factor(0.5);
    return 0;
}

/* Function name: query_spell_level
 * Description:   Internally used by the standing system in the pots.
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 1;
}

/*
 * Function name: is_valid_fartell_target
 * Description: This function checks whether the specified target is a valid
 *              target. If the caster is not a full priest he is limited to
 *              target people in his memory.
 * Returns: 1 on valid target, 0 on invalid target.
 */
public int is_valid_fartell_target(object caster, object target)
{
    find_player("navarre")->catch_msg("The type of the target is: " +typeof(target));
	find_player("navarre")->catch_msg("The object is present and is: " + file_name(target));
	find_player("navarre")->catch_msg("Is target an npc?" + target->query_npc());
	
	if (target->query_npc())
	{
	    find_player("navarre")->catch_msg("Exiting correctly\n");
	    return 0;
	}
	
    if (!caster->query_met(target) &&
        caster->query_priest_level() <= GUILD_LEVEL_INITIATE)
    {
        return 0;
    }
    return 1;
}

/*
 * Function:    hook_fartell_no_message
 * Description: Override to customize the message for when the caster doesn't
 *              specify a text to send.
 */
public void
hook_fartell_no_message(object caster)
{
    caster->catch_tell("You need to specify a message!\n");
}
/*
 * Function:    hook_fartell_target_unavailable
 * Description: Override to customize the message for when the target cannot
 *              be reached. This includes invis wizards
 */
public void
hook_fartell_target_unavailable(object caster, string target)
{
    caster->catch_tell(C(target) + " is not present in the realms.\n");
}
/*
 * Function:    hook_fartell_target_not_valid
 * Description: Override to customize the message for when the target cannot
 *              be reached because is_valid_fartell_target returns false
 */
public void
hook_fartell_target_not_valid(object caster, string target)
{
    caster->catch_tell("You do not remember any " +
                        C(target) + ".\n");
}


/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    // This sends the message only to the people in the specified room that
    // can see the caster.    
    my_tell_roombb(environment(caster), QCTNAME(caster) + " closes " +
                HIS(caster) + " eyes and whispers something.\n",
                caster);
     
    caster->catch_tell("Across the distance, you whisper to " +
                       C(target->query_name()) + ":\n" +
                       break_string(message_text, 60, "\t") + "\n");
                       
    string caster_name = target->query_met(caster) ? caster->query_name() :
                         LANG_ADDART(caster->query_race_name());
                         
    target->catch_tell("As if from behind you, you hear " + caster_name +
                       " whispering:\n" +
                       break_string(message_text, 60, "\t") + "\n");
}

/*
 * Function: concentrate_msg
 * Description: This function masks the concentrate message from the original
 *              spell file to customize the description when preparing for a
 *              spell.
 * 
 * @see /d/Genesis/specials/spell.c
 *
 * @param caster The object representing the player casting this spell.
 * @param targets A collection of targets this spell is aimed at.
 * @param arg  The arguments passed to the 'cast' command.
 */
public void
concentrate_msg(object caster, mixed* targets, string arg)
{
    caster->catch_tell("You clutch your black medallion and pray to the " +
                       "Queen of Darkness.\n");
                       
    tell_room(environment(caster), QCTNAME(caster) + " clutches " +
              HIS(caster) + " medallion and prays to the Queen of " +
              "Darkness.\n",
              ({caster}), caster);
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_fartell_ingredients(object caster)
{
    return ({ "copper coin" });
}
