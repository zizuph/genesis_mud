/*
 * Minstrel's team bravuro SS_DIS statboost song - Arman 2019
 */

inherit "/d/Genesis/specials/std/spells/unfinished/aura.c";

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
 * Function name:   meet_living
 * Description:     Tells us of new living entities in our vicinity.
 * Arguments:       (object) spell_object - The original aura spell object
 *                  (object) target - The living met in the room
 *                  (object) caster - The one with the aura
 * Returns:         Nothing
 */ 
public void
meet_living(object spell_object, object target, object caster)
{
    caster->catch_msg("Meet living.\n");
    if (member_array(target, caster->query_team_others()) > -1 && 
        !has_effect_object(target))
        add_aura_effect(spell_object, caster, target);
    
} /* meet_living */

public void
leave_team(object spell_object, object member)
{
    object caster = spell_object->query_effect_caster();
    
    caster->catch_msg("Left team.\n");
    if (has_effect_object(member))
        remove_aura_effect(spell_object, caster, member);
}

public void
join_team(object spell_object, object member)
{
    object caster = spell_object->query_effect_caster();
    
    caster->catch_msg("Joined team.\n");
    if (!has_effect_object(member))
        add_aura_effect(spell_object, caster, member);
}

/*
 * Function name:   config_aura_spell
 * Description:     Config function for aura spells. Redefine this in your own
 *                  aura spells to override the defaults.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_aura_spell()
{
    ::config_aura_spell();

    set_ability_group(GUILD_NAME);
    set_spell_name("bravuraa");
    set_spell_desc("a song encouraging team bravery");

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 25);
    set_spell_form(SG_VOCAL, 25);
    set_spell_task(TASK_HARD);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_fail(minstrel_perform_fail);

    set_aura_effects(({MIN_SPELLS + "obj/brave_test_obj"}));

    add_function_pointer("init_living", &meet_living());
    add_function_pointer("team_join", &join_team());
    add_function_pointer("team_leave", &leave_team());

} /* config_aura_spell */

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
/*
    if (!IN_ARRAY("brave", song_list))
    {
        return 0;
    }
*/
    if (MEMBER(player))
    {
        return 1;
    }
    
    return 0;
}


/*
 * Function:    query_aura_ingredients
 * Description: This function defines what components are required for
 *              this stat boost spell.
 */
public string *
query_aura_ingredients(object caster)
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
        caster_message = "You begin performing an inspiring Song of " +
            "Battle!\n";
        watcher_message = QCTNAME(caster) + " begins performing an " +
            "inspiring Song of Battle!\n";
    }
    else
    {
        caster_message = "You begin performing a powerful Song of " +
            "Battle, inspiring yourself and " +COMPOSITE_LIVE(team)+ "!\n";
        watcher_message = QCTNAME(caster) + " begins performing an " +
            "inspiring Song of Battle!\n";
    }
        
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
hook_describe_cast_aura(object caster, object * targets)
{
/*
    if(sizeof(targets) == 1)
    {
        caster->catch_tell("A powerful Song of Battle fills the " +
            "air and strengthens your heart as you prepare for combat.\n");
    }
    else foreach(object target: targets)
    {
        object *team = targets - ({ target });

        target->catch_tell("A powerful Song of Battle fills the air and " +
            "strengthens your heart and those of your companions - " +
            COMPOSITE_LIVE(team)+ " - as you prepare for combat.\n");
    } 

    tell_room(environment(caster), "A powerful Song of Battle fills " +
        "the air and seems to inspire " +COMPOSITE_LIVE(targets)+ " " +
        "to acts of bravery in combat.\n", targets);
*/
}

/*
 * Function name:   resolve_aura_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_aura_spell(object caster, object *targets, int *resist, int result,
                   mapping spell_input)
{
    hook_describe_cast_aura(caster, targets);
} /* resolve_aura_spell */

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_aura_effect_started(object spell_object)
{
    object  caster = spell_object->query_effect_caster();
    object *team = caster->query_team_others() + ({ caster });
    object *success = map(team, &add_aura_effect(spell_object, caster,));

    spell_object->catch_tell("A powerful Song of Battle fills the air and " +
            "strengthens your heart as you prepare for combat.\n");

    tell_room(environment(caster), "A powerful Song of Battle fills " +
        "the air and seems to inspire " +COMPOSITE_LIVE(spell_object)+ " " +
        "to acts of bravery in combat.\n", ({ spell_object }));

} /* hook_spell_effect_started */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_aura_effect_ended(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    object *team = caster->query_team_others() + ({ caster });
    map(team, &remove_aura_effect(spell_object, caster,));
    
    spell_object->catch_tell("You feel the inspiration of your Song " +
         "of Battle leave you.\n");


} /* hook_spell_effect_ended */