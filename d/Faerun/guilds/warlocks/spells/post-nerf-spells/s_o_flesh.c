/*
 * Sculptor of Flesh - Temporarily alter your looks
 *
 * * - Added layman caster postfix balance variables.  Nerull 2019
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/statboost";


/*
 * Function:    config_statboost_spell
 * Description: Config function for stat boost spells. Redefine this in your
 *              own stat boost spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_statboost_spell()
{
    set_spell_name("urhagash");
    set_spell_desc(" - Sculptor of Flesh: Modify body to be stronger and tougher");
    
    set_spell_element(SS_ELEMENT_EARTH,  50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
    //set_spell_mana(30);
    set_spell_task(TASK_HARD);
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
   
    set_spell_target(spell_target_caster);
   
    set_spell_object(WARLOCK_SPELLOB_DIR + "s_o_flesh_obj");
}


/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
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
        if (player->query_guild_level_lay() >= SCULPTOROFFLESH_UNLOCK)
        {
            return 1;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(player->query_name()))
    {
        if (player->query_guild_level_occ() >= SCULPTOROFFLESH_UNLOCK)
        {
            return 1;
        }
    }

    return 0;
}


public int
check_valid_action(object caster, mixed * targets, 
string arg, int execute = 0)
{
    int a = 0;
    
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast sculptor of flesh on yourself!\n");
        return 0;
    }
    

    if (present("_warpreality_object_", caster))
    {
        caster->catch_tell("The warped reality around you interferes in "
        +"casting Urhagash!\n");
        return 0;
    }
    
    
    
    if (present("_eldritch_sight_object_", this_player()))
    {
        a = a + 1;
    }
    
    if (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player()))
    {
        a = a + 1;
    }
    
    if (a >= 2)
    {   
        this_player()->catch_tell("You have too many active magical spells "
        +"in order to cast this spell.\n");
            
        return 0;
    }
    
    if (this_player()->query_war_defensive() == 1) 
    {   
        // stat boosted, combat aid provided. Total 15 c aid.
        add_stat_boost(SS_CON, 15);
        
        return 1;
    }
    
    add_stat_boost(SS_STR, 30);
    
    return 1;
}


/*
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this stat boost spell.
 */
public string *
query_statboost_ingredients(object caster)
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
    
    return ({ "_sculptor_charge" });
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are under the effect of Urhagash already.\n");
}


/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You are not sufficiently prepared for Urhagash!\n");
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
 * Function:    hook_describe_cast_statboost
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_statboost(object caster, object * targets)
{
}



