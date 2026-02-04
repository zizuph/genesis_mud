/*
 * Minstrel's team animato mana regen song - Arman 2019
 *
 * While mana regeneration for layman magical guilds is usually
 * not appropriate, in this case - seeing it is a low combat aid
 * and the team-support nature of the minstrels - is ok.
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "unfinished/regen_mana";

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

public object *
spell_target_present_team(object actor, string str)
{
    object *team = actor->query_team_others() & 
        all_inventory(environment(actor)) + ({ actor });

    team += ({ actor });

    return team;
}

/*
 * Function:    config_regen_mana_spell
 * Description: Config function for mana regeneration spells. Redefine this in your
 *              own at will spells to override the defaults.
 */
public varargs void
config_regen_mana_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("animato");
    set_spell_desc("a tune that mentally refreshes your companions");

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 45);
    set_spell_form(SG_VOCAL, 45);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_fail(minstrel_perform_fail);

    set_spell_target(spell_target_present_team);

    // songs influenced by a combination of TS_DEX and TS_DIS 
    // rather than TS_INT
    set_ability_stats( ({ SKILL_AVG, TS_DEX, TS_DIS, SKILL_END }) );
    set_spell_combat_aid(10.0);

    // Spell effect object
    set_spell_object(MIN_SPELLS + "obj/animato_obj");

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

    if (!IN_ARRAY("animato", song_list))
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
 * Function:    query_regen_mana_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */
public string *
query_regen_mana_ingredients(object caster)

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

    if(query_active_lost_muse_effect(caster, "animato"))
    {
        caster->catch_tell("You can only perform one Song of Power inspired " +
            "by a Lost Muse at a time!\n");
        return 0;
    }

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if(caster == target)
        write("You are already performing Animato.\n");
    else
        write(QCTNAME(target)+ " is already mentally refreshed from the " +
    	    "song Animato.\n");
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew your mentally refreshing Song of Power.\n");
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
    object *team = targets - ({ caster });

    if(!sizeof(team))
    {
        caster_message = "You begin performing a mentally refreshing Song of " +
            "Power!\n";
        watcher_message = QCTNAME(caster) + " begins performing a " +
            "mentally refreshing Song of Power!\n";
    }
    else
    {
        caster_message = "You begin performing a mentally refreshing Song of " +
            "Power for yourself and " +COMPOSITE_LIVE(team)+ "!\n";
        watcher_message = QCTNAME(caster) + " begins performing a " +
            "mentally refreshing Song of Power!\n";
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}
