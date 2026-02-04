/*
 * Minstrel's soothe heal song - Arman 2019
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/calm";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#include <macros.h>
#include <tasks.h>

#include "minstrel_spell_hooks.h"

#define HIS(x)        ((x)->query_possessive())

public object *
spell_target_present_team(object actor, string str)
{
    object *team = actor->query_team_others() & 
        all_inventory(environment(actor)) + ({ actor });
/*
    if (!sizeof(team))
    {
        actor->catch_tell("You are not in a team, so cannot " +
            "perform pax.\n");
        return ({});
    }
*/
    team += ({ actor });

    return team;
}

/*
 * Function:    config_calm_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_calm_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("pax");
    set_spell_desc("a peaceful tune calming you and your team");

    // Standard cast time
    set_spell_time_factor(1.0);  

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_HARD);
    set_spell_fail(minstrel_perform_fail);

    set_spell_target(spell_target_present_team);

    set_spell_resist(spell_resist_illusion);

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 20);
    set_spell_form(SG_VOCAL, 20);
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_calm_ingredients(object caster)
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

    if (!IN_ARRAY("peace", song_list))
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
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // Combat aid impacted by damage to the instrument to
    // a maximum reduction of 45% before the instrument breaks.

    float caid_mod = 100.0;
    object instrument = present("minstrel_instrument", this_player());
    int instrument_damage = instrument->query_damage();

    caid_mod = 100.0 - itof(instrument_damage * 5);
    
    return caid_mod;
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

/*
 * Function:    resolve_calm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_calm_spell(object caster, mixed * targets, int * resist, int result)
{

}

/*
 * Function name: desc_calm_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                mapping calm_amounts - the amount calmed for each target
 */
public void
desc_calm_cast(object caster, mapping calm_amounts)
{
    object * targets = m_indices(calm_amounts);
    object * other_targets = targets - ({ caster });

    if(sizeof(targets) == 1)
    {
        caster->catch_tell("You feel the Tune of Peacefulness calm " +
            "your heart of fear and unease.\n");
    }
    else foreach(object target: targets)
    {
        object *team = targets - ({ target });

        target->catch_tell("A peaceful tune fills the air and " +
            "calms you and your companions - " +
            COMPOSITE_LIVE(team)+ " - of fear and unease.\n");
    } 

    tell_room(environment(caster), "A peaceful tune fills " +
        "the air and seems to calm " +COMPOSITE_LIVE(targets)+ " " +
        "of fear and unease.\n", targets);
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
        caster_message = "You begin performing a calming Tune of " +
            "Peacefulness.\n";
        watcher_message = QCTNAME(caster) + " begins performing a " +
            "calming tune.\n";
    }
    else
    {
        caster_message = "You begin performing a Tune of " +
            "Peacefulness, calming yourself and " +COMPOSITE_LIVE(team)+ "!\n";
        watcher_message = QCTNAME(caster) + " begins performing a " +
            "calming Tune of Peacefulness.\n";
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}
