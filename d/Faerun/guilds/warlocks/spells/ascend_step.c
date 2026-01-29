/*
 * Ascentant Step - Leave no tracks behind you
 * By Nerull, June 2017
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
inherit SPELL_DIR + "propchange_base";


/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */
public void
config_propchange_spell()
{
    set_spell_name("uraene");
    set_spell_desc(" - Ascendant Step: Protects against tracking");

    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ABJURATION, 10);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_task(TASK_ROUTINE);
    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);

    set_spell_target(spell_target_caster);

    set_spell_can_be_renewed(1);
   
    set_shadow_filename(WARLOCK_SPELLOB_DIR + "ascendstep_sh");
}


/*
 * Function:    query_protect_dragonfear_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_propchange_ingredients(object caster)
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
    
    return ({ "_ascendstep_charge" });
}


/* 
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result,
mapping spell_input)
{
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

    if (WARLOCK_MASTER->is_lay_warlock(player->query_name()))
    {
        if (player->query_guild_level_lay() >= ASCENDSTEP_UNLOCK)
        {
            return 1;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(player->query_name()))
    {
        if (player->query_guild_level_occ() >= ASCENDSTEP_UNLOCK)
        {
            return 1;
        }
    }

    return 0;
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


public void
hook_describe_cast_propchange(object caster, object* targets)
{
    //caster->catch_tell("You cast a prop changeeee spell upon " +
      //                 COMPOSITE_LIVE(targets) + ".\n");
    //caster->tell_watcher(QCTNAME(caster) 
    //+ " casts a prop changeeee spell.\n", ({}) );
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
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are under the effect of Uraene already.\n");
}