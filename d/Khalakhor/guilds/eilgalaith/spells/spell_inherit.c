/**********************************************************************
 * - spell_inherit.c                                                - *
 * - Created by Tomas and Damaris                                   - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
 
inherit "/d/Genesis/newmagic/components";
inherit "/d/Genesis/newmagic/targeting";
inherit "/d/Genesis/newmagic/resist";
inherit "/d/Genesis/newmagic/spell";

#include <language.h>
#include <tasks.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

// Extra targeting functions.

public object *
spell_target_caster_environment(object caster, string str)
{
    return ({ environment(caster) });
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, object *targets, string arg)
{

    caster->catch_tell("You close your eyes and concentrate upon the "+
      "power of the mystic vine.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) +" starts concentrating "+
      "deeply.\n");
}
/* 
 * Function name: break_spell
 * Description:   Take special actions when casting is broken.
 * Arguments:     1. (object) The caster
 *                2. (object) The object responsible for breaking the spell
 */
public void
break_spell(object caster, object breaker)
{
    caster->catch_tell("Your concentration is broken and you feel the "+
      "power of the mystic vine slip away.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
          - ({ caster }))->catch_msg(QCTNAME(caster) +" loses "+
          "concentration.\n");
}

/*
 * Function name: abort_spell
 * Description:   Take special actions when casting is aborted
 * Arguments:     1. (object) The caster.
 */
public void
abort_spell(object caster)
{
    caster->catch_tell("You open your eyes and relax.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
          - ({ caster }))->catch_msg(QCTNAME(caster) +" relaxes.\n");
}
void
default_spell_config()
{
    set_spell_fail("You feel the power of the mystic vine slip away.\n");
    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);
    // Dont allow them to move while casting
    set_spell_stationary(1);
    // We are a peaceful oriented guild.
    set_spell_peaceful(1);
    // Allow them to cast while unable to see.
    set_spell_visual(0);
    

}

// Redefined hooks.
void
hook_combat_fail(object *combatants)
{
    write("You are unable to concentrate on your summons while in combat with "+
      FO_COMPOSITE_ALL_LIVE(combatants, this_player()) + ".\n");
}

public void
hook_room_no_magic_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("For some reason you are unable to concentrate "+
          "upon the power, of the mystic vine, as if resisted by some "+
          "strange property within this very room.\n");
    }
}

void
hook_no_skills_fail()
{
    write("You are not skilled enough to maintain your "+
      "concentration on this spell!\n");
}

void
hook_no_mana_fail()
{
    write("You are too mentally exhausted to maintain your spell.\n");
}

void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You do not have the proper components to complete the spell!\n");
}

void
hook_targets_gone()
{
    write("The target of your summons seems to dissappeared.\n");
}

void
hook_stun_fail()
{
    write("You are to stunned to concentrate on your spell!\n");
}
