/*
 * Basic spell inherits borrowed from Heralds
 * -- Finwe, Feb 2005
 */
inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/spell_config";

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

// Wild Elf Spell Defaults

void
default_conc_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You pause for a moment and begin to commune with Nature.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) + " pauses for a moment " +
      "and begins to commune with Nature.\n");
}

void
default_wild_elf_spell_config()
{
    set_spell_conc_message(default_conc_msg);
    set_spell_fail("Your communion to Nature goes unanswered.\n");
    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);
    // We can move around a bit in order to cast.
    set_spell_stationary(0);
    // We are a peaceful oriented guild.
    set_spell_peaceful(1);
    // We can call Mother Nature for help.
    set_spell_visual(0);
    set_spell_break("Your communion with Nature is broken.\n");
    set_spell_abort("You decide to not to call upon Nature for aid.\n");
}

// Redefined hooks.
void
hook_combat_fail(object *combatants)
{
    write("You are unable to call upon the powers of Nature while " +
        "fighting with " + FO_COMPOSITE_ALL_LIVE(combatants, this_player()) + 
        ".\n");
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
	write("You're unable to call upon the powers of Nature here.\n");
    }
}

void
hook_no_skills_fail()
{
    write("You lack the skills to envoke that spell!\n");
}

void
hook_no_mana_fail()
{
    write("You are too mentally exhausted to attempt this spell.\n");
}

void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You do not have the proper components to do this spell!\n");
}

void
hook_targets_gone()
{
    write("The target of your spell has dissappeared.\n");
}

void
hook_stun_fail()
{
    write("You are to stunned to complete your spell!\n");
}
