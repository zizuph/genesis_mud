/*
 * Minstrel's bravuro SS_DIS statboost song - Arman 2019
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/statboost";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#include "minstrel_spell_hooks.h"


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
    set_ability_group(GUILD_NAME);
    set_spell_name("bravuro");
    set_spell_desc("a song encouraging bravery in battle");

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 15);
    set_spell_form(SG_VOCAL, 15);
    set_spell_task(TASK_HARD);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_fail(minstrel_perform_fail);

    set_spell_target(spell_target_one_present_living);

    // Spell effect object
    set_spell_object(MIN_SPELLS + "obj/brave_obj");

    // stat SS_DIS boosted, to a max of 30 combat aid. 
    add_stat_boost(SS_DIS, 30);

}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    // We don't allow the "cast" verb to be used or
    // the songs of power to show in the spells list
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    string * song_list = SONGBOOK_MANAGER->query_power_songs(player);

    if (!IN_ARRAY("brave", song_list))
    {
        return 0;
    }

    if (MEMBER(player))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this stat boost spell.
 */
public string *
query_statboost_ingredients(object caster)
{
    return ({ });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "vocal, instrument";
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object instrument = present("minstrel_instrument", caster);

    if(query_spell_form_skill() == SG_INSTRUMENTAL ||
       query_spell_element() == SG_INSTRUMENTAL)
    {
        // The instrument is broken if it has 10 damage.
        if(instrument->query_damage() > 9)
        {
            caster->catch_tell(instrument->query_damage_desc()+ " You cannot " +
                "perform with it in such a state!\n");
            return 0;
        }
    }

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if(caster == target)
        write("You are already inspired by the Song of Battle.\n");
    else
        write(QCTNAME(target)+ " is already inspired by the " +
    	    "Song of Battle.\n");
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
    object target = targets[0];

        caster_message = "You begin performing an inspiring Song of " +
            "Battle!\n";
        watcher_message = QCTNAME(caster) + " begins performing an " +
              "inspiring Song of Battle!\n";
        
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
