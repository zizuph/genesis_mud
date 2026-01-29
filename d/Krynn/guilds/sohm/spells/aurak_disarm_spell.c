/*
 * Disarm spell for aurak npc
 *
 * Created by Arman 2018
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "unfinished/disarm";

/*
 * Function:    config_disarm_spell
 * Description: Config function for disarm spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public varargs void
config_disarm_spell()
{
    set_spell_name("aurakdisarm");
    set_spell_desc("Aurak spell of disarming");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_task(TASK_ROUTINE);    
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_combat_aid(45.0);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_object(SPELL_DIR + "unfinished/disarm_obj");

}

/*
 * Function:    query_disarm_ingredients
 * Description: This function defines what components are required for
 *              this disarm spell.
 */
public string *
query_disarm_ingredients(object caster)
{
    return ({  });
}


/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    // For aurak npc only    
    return 0;
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

        caster_message = "Your eyes narrow in concentration as you begin chanting " +
            "magical words of mind manipulation and domination.\n";
        watcher_message = QCTNAME(caster) + " narrows " + caster->query_possessive() + 
              " eyes in concentration and begins reciting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
 
    return 1;
}

public void
hook_describe_disarm(object caster, mixed * targets, int result)
{
    caster->catch_msg("You extend your clawed hands towards "+ COMPOSITE_LIVE(targets) +
		      " and feel mystical energy shoot out from your hands.\n");
    targets->catch_msg(QCTNAME(caster) + " extends " + HIS(caster) +
			  " clawed hands, and mystical energy shoots out towards you.\n");
    tell_room(environment(caster), QCTNAME(caster) + " extends " + HIS(caster) + 
	      " clawed hands towards " + COMPOSITE_LIVE(targets) +
	      ", causing a flash of energy to ignite between them.\n",
	      ({ caster }) + targets, caster);
}

