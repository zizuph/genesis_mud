/*
 * Warlock Infusion spell
 *
 * Originaly created by Arman, used by Nerull 2018
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "refresh";


/*
 * Function:    config_refresh_spell
 * Description: Config function for refresh spells. Redefine this in your
 *              own refresh spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_refresh_spell()
{
    set_spell_name("urkenu");
    set_spell_desc(" - Infusion: Reduces fatigue ");
    
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ILLUSION, 15);

    set_spell_task(TASK_ROUTINE);
    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);
}


public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return 1;
    }
    
    // If we are testing spells regardless of rank and selection.
    if (SPELLTESTING == 1)
    {
        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
            >= INFUSION_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
            >= INFUSION_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
        }
    }

    return 0;
}


/*
 * Function:    query_refresh_ingredients
 * Description: This function defines what components are required for
 *              this refresh spell.
 */
public string *
query_refresh_ingredients(object caster)
{
    // If we are testing spells, no components
    if (SPELLTESTING_NOCOMPS == 1)
    {
        return ({ });
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return ({ });
    }
    
    return ({ "_infusion_charge" });
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    return 1;
}


/*
 * Function:    resolve_refresh_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_refresh_spell(object caster, mixed * targets, int * resist, int result)
{
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
    string caster_message, watcher_message;

    caster_message = "As you surreptitiously whisper the long "
    +"forgotten words, the sounds reverberates in increasing "
    +"intensity, only to fade as you draw arcane powers from the "
    +"shadows!\n";
    
    watcher_message = "A chorus of eerie whispers permeate the area in "
    +"increasing intensity, only to fade again as "+QCTNAME(caster)
    +" turns inwards.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function name: desc_refresh_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object * targets - the targets 
 *                int amount - the amount refreshed
 */
public void
desc_refresh_cast(object caster, object * targets, int amount)
{
    object tar = targets[0];
    int heal = amount;
    string heal_desc;
    switch(heal)
    {
       case 0..10:
         heal_desc = " slightly";
         break;
       case 11..20:
         heal_desc = " somewhat";
         break;
       case 21..30:
         heal_desc = "";
         break;
       case 31..40:
         heal_desc = " greatly";
         break;
       case 41..100:
         heal_desc = " immensly";
         break;
       default:
         heal_desc = "";
         break;
    }
    
    if (tar == caster)
    {
        caster->catch_tell("You feel" +heal_desc+ " infused with new "
        +"vigor.\n");
            
        tell_room(environment(caster), QCTNAME(caster) +
	    " looks less fatigued.\n", 
        targets);
    }
    else
    {
        caster->catch_tell("You channel the powers of your " +
	    "patron at "+tar->query_the_name(caster) + ", and " + 
        tar->query_pronoun() +" looks" +heal_desc+ " affected.\n");
        
        tar->catch_tell(caster->query_The_name(tar) + " looks " +
	    "discreetly at you, and you suddenly feel" +
	    heal_desc+ " infused with new vigor!\n");
        
        tell_room(environment(caster), QTNAME(tar) + 
        " suddently looks less fatigued.\n",
	    ({ caster, tar }), caster);
    }
}
