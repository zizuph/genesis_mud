/**********************************************************************
 * - spell_inherit2.c                                               - *
 * - Created by Damaris 2/2002                                      - *
 **********************************************************************/
inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/spell_config";
#include "../guild.h" 
#include <language.h>
#include <tasks.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

public object *
spell_target_caster_environment(object caster, string str)
{
    return ({ environment(caster) });
}

void
default_aura_conc_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You close your eyes and concentrate through the "+
      "power of the mystic vine.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) +" concentrates quietly.\n");
}

void
default_aura_spell_config()
{
    set_spell_conc_message(default_aura_conc_msg);
    set_spell_fail("Your spell fails.\n");
    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);
    set_spell_stationary(0);
    set_spell_break("Your concentration on your spell is "+
      "broken.\n");
    set_spell_abort("You decide to not cast your spell.\n");
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
	write("For some reason you are unable cast your spell, it is "+
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
    write("You are too mentally exhausted to attempt this spell.\n");
}

void
hook_targets_gone()
{
    write("The target of your spell seems to dissappeared.\n");
}

void
hook_stun_fail()
{
    write("You are to stunned to complete your spell!\n");
}
