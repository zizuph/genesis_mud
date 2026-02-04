/*
 * Minstrel's concerto skill increase song - Arman 2019
 */

#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "shadow";

#include "minstrel_spell_hooks.h"

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("concerto");
    set_spell_desc("a focusing song improving instrumental and singing");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_task(TASK_HARD);
    set_spell_fail(minstrel_perform_fail);

    set_spell_class(SPELL_CLASS_1);
    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 45);
    set_spell_form(SG_VOCAL, 45);

    // Can only cast on self
    set_spell_target(spell_target_caster);

    set_shadow_filename(MIN_SPELLS + "obj/concerto_sh");
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{ 
    return ({  });
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

    if (!IN_ARRAY("concerto", song_list))
    {
        return 0;
    }

    if (MEMBER(player))
    {
        return 1;
    }
    
    return 0;
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

    if(query_active_lost_muse_effect(caster, "concerto"))
    {
        caster->catch_tell("You can only perform one Song of Power inspired " +
            "by a Lost Muse at a time!\n");
        return 0;
    }

    return 1;
}

// HOOKS TO BE DEFINED

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
    string voice = caster->query_vocal_skill_adverb();

    caster_message = "You " +voice+ " attempt Concerto, and the air " +
        "stirs with the beauty and power of the music.\n";
    watcher_message = QCTNAME(caster) +" " +voice+ " attempts a Song of " +
        "Power, and the air stirs with the beauty and power of the music.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
}
