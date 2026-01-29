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

public object *
spell_target_herald_robe(object caster, string str)
{
    object robe = present("_herald_robe_", caster);

    if (!objectp(robe))
    {
	caster->catch_tell("You are unable to pray for this spell without "+
	  "your robe!\n");
	return ({ });
    }
    if (!robe->query_worn())
    {
	caster->catch_tell("Your "+robe->short()+" must be worn "+
	  "in order to pray for this spell.\n");
	return ({ });
    }
    return ({ robe });
}

// Herald spell default configurations

void
default_valar_conc_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You kneel down and offer a silent prayer "+
      "to the Valar.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) +" kneels down and "+
      "begins a prayer.\n");
}

void
default_herald_spell_config()
{
    set_spell_conc_message(default_valar_conc_msg);
    set_spell_fail("Your prayer remains unanswered.\n");
    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);
    // We can move around a bit in order to cast.
    set_spell_stationary(0);
    // We are a peaceful oriented guild.
    set_spell_peaceful(1);
    // We can call apon the aid of the Valar while we can't see.
    set_spell_visual(0);
    set_spell_break("Your concentration on your prayer is "+
      "broken and remains unheard.\n");
    set_spell_abort("You decide to not to call upon the Valar "+
      "for aid.\n");
}

// Redefined hooks.
void
hook_combat_fail(object *combatants)
{
    write("You are unable to call upon this prayer while in combat with "+
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
	write("For some reason you are unable to pray for aid, as if "+
	  "resisted by some strange property within this very room.\n");
    }
}

void
hook_no_skills_fail()
{
    write("You are not skilled enough to ask for this prayer!\n");
}

void
hook_no_mana_fail()
{
    write("You are too mentally exhausted to attempt this prayer.\n");
}

void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You do not have the proper components to make this prayer!\n");
}

void
hook_targets_gone()
{
    write("The target of your prayer seems to dissappeared.\n");
}

void
hook_stun_fail()
{
    write("You are to stunned to complete your prayer!\n");
}
