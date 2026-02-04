/*
 * Minstrel's enemy panic debuff song - Arman 2019
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "paranoia";

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

static mapping  enemies = ([]);
static int      restrict_targets = 3;

public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You are not in combat so have no target for your " +
        "Song of Aggression.\n");
}

public object *
spell_target_present_enemies(object actor, string str)
{
    enemies[actor] = (object *)actor->query_enemy(-1) &
                     all_inventory(environment(actor));
    object * teammates = actor->query_team_others();

    if (sizeof(teammates) > 0)
    {
        foreach(object mate: teammates)
        {
            enemies[actor] |= (object *)mate->query_enemy(-1) &
                     all_inventory(environment(mate));
        }
        // dump_array(enemies[actor]);
    }
    
    /* Restricting the targets based on preset values */
    if (restrict_targets && sizeof(enemies[actor]) > restrict_targets)
        enemies[actor] = exclude_array(enemies[actor],
                                       restrict_targets,
                                       sizeof(enemies[actor]) - 1);
    
    if (!sizeof(enemies[actor]))
    {
        hook_no_present_targets(actor, str);
        return ({});
    }
    
    return enemies[actor];
}

/*
 * Function:    config_paranoia_spell
 * Description: Config function for paranoia spells. Redefine this in your
 *              own paranoia spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_paranoia_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("bellicoso");
    set_spell_desc("an aggressive song causing fear in enemies");

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 45);
    set_spell_form(SG_VOCAL, 45);
    set_spell_task(TASK_HARD);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_can_be_renewed(0);
    set_spell_can_be_resisted(1);
    set_spell_fail(minstrel_perform_fail);
    set_spell_resist(spell_resist_illusion); 

    set_spell_target(spell_target_present_enemies);
    
    set_spell_class(SPELL_CLASS_1);

    // songs influenced by a combination of TS_DEX and TS_DIS 
    // rather than TS_INT
    set_ability_stats( ({ SKILL_AVG, TS_DEX, TS_DIS, SKILL_END }) );

    // Spell effect object
    set_spell_object(MIN_SPELLS + "obj/bellicoso_obj");
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

    if (!IN_ARRAY("bellicoso", song_list))
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
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast. 
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" was unaffected by your Song of Aggression.\n");
    target->catch_msg("You were unaffected by " + QTPNAME(caster)+" song.\n");
}

/*
 * Function:    resolve_paranoia_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell 
 */
public void
resolve_paranoia_spell(object caster, mixed * targets, int * resist, int result)
{

}

/*
 * Function:    query_paranoia_ingredients
 * Description: This function defines what components are required for
 *              this paranoia vision spell.
 */
public string *
query_paranoia_ingredients(object caster)
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

    if(query_active_lost_muse_effect(caster, "bellicoso"))
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
        write("You are already performing Bellicoso!\n");
    else
        write(target->query_The_name(caster)+ 
            " is already affected by your Song of Aggression!\n");
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew your performance of Lento!\n");
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

        caster_message = "You pour your aggression into a Song of " +
            "Power towards " +COMPOSITE_LIVE(targets)+ "!\n";
        watcher_message = QCTNAME(caster) + " begins an aggressive " +
            "Song of Power towards " +COMPOSITE_LIVE(targets)+ "!\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

