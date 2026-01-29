/*
 * A darkness spell that clones a darkness object in to
 * the room of the caster and modifies the darkness room message
 * of the room.
 * 
 * Based on the sulambar Morgul Mage spell which spawns a cloud in
 * to the room of the mage.
 *
 * Coded by Arman 2016.
 */

#pragma strict_types

#include <filter_funs.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";
#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

public string *query_darkness_ingredients(object caster);

public nomask void
config_spell()
{
    set_spell_name("whedabra");
    set_spell_desc("Gloom - summons dark shadows that obscures vision");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ILLUSION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);

    set_spell_target(spell_target_caster_environment);
    set_ability_target_verify(0);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_ingredients(query_darkness_ingredients);
    set_spell_object(SOHM_SPELL_OBJS + "gloom_obj");
}

public string *query_darkness_ingredients(object caster)
{
    return ({ "skullcap" });
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
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"whedabra_memorised");
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

        caster_message = "You begin weaving your hands through the air while chanting " +
            "'whedabra', magically pulling strands of darkness towards you.\n";
        watcher_message = QCTNAME(caster) + " begins weaving " + HIS(caster)+ " hands " +
           "through the air while chanting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets  - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    make_spell_object(query_spell_object(), caster, targets, resist, result);
}
