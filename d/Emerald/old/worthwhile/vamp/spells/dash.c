#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include "../guild.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>
#include <std.h>

string dircmd;

public object *
parse_args(object caster, string arg)
{
    string tmp;

    if (!strlen(arg))
    {
        caster->catch_tell("Dash where?\n");
        return ({});
    }
  
    if (!CAN_SEE_IN_ROOM(caster))
    {
    	caster->catch_tell("Your path is too dark to see.\n");
        return ({});
    }
  
    if (strlen(tmp = SECURITY->modify_command(arg, environment(this_player()))))
    {
        arg = tmp;
    }
  
    tmp = (explode(arg, " ") - ({ "" }))[0];
    if (member_array(tmp, environment(this_player())->query_exit_cmds()) < 0)
    {
        caster->catch_tell("Dash where?\n");
        return ({});
    }

    dircmd = arg;

    return ({ caster });
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0 - configuration successful
 *                1 - configuration unsuccessful, abort spell
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (caster && 
        (caster->query_encumberance_weight() > 75) ||
	(caster->query_encumberance_volume() > 75))
    {
    	write("You are too encumbered.\n");
    	return 1;
    }

    set_spell_name("dash");
    set_spell_desc("dash");
    set_spell_time(0);
    set_spell_mana(20);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_ingredients(({}));
    set_spell_resist(0);
    set_spell_peaceful(0);

    set_spell_target(parse_args);
    return 0;
}

int f(object ob)
{
    return (ob->query_wiz_level() ||
        (IS_MEMBER(ob) && CAN_SEE_IN_ROOM(ob) && CAN_SEE(ob, this_player())));
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int footprints;
    object *team_present;
    string msgin, msgout;

    set_this_player(caster);
  
    if (!(footprints = this_player()->query_prop(LIVE_I_NO_FOOTPRINTS)))
    {
        this_player()->add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    }

    // It would be nice to check that the move is successful before giving
    // any messages, but I'll be lazy....
  
    msgout = " disappears in a flash.\n";
  
    if (this_player()->query_invis())
    {
	say(({ "(" + METNAME + ")" + msgout,
	     ART_NONMETNAME + msgout,
	     "" }));
    }
    else
    {
	say(({ METNAME + msgout,
	     ART_NONMETNAME  + msgout,
	     "" }));
    }
  
    filter(all_inventory(environment(this_player())) - ({ this_player() }),
        f)->catch_msg("With your keen perception, you " +
        "notice that " + QTNAME(this_player()) + " left " + dircmd + ".\n");
  
    this_player()->add_prop(OBJ_I_INVIS,
        this_player()->query_prop(OBJ_I_INVIS) + 99);
  
    team_present = this_player()->query_team() &
        all_inventory(environment(this_player()));
  
  // Temporarily remove anyone whom we are leading in a team
    map(team_present, &(this_player())->team_leave());
  
  // Execute the exit command
    this_player()->command(dircmd);
  
    this_player()->add_prop(OBJ_I_INVIS,
        this_player()->query_prop(OBJ_I_INVIS) - 99);
  
    msgin = " dashes in.\n";
  
    if (this_player()->query_invis())
    {
        say(({ "(" + METNAME + ")" + msgin, ART_NONMETNAME + msgin, "" }));
    }
    else
    {
        say(({ METNAME + msgin, ART_NONMETNAME + msgin, "" }));
    }
  
    if (!footprints)
    {
        this_player()->remove_prop(LIVE_I_NO_FOOTPRINTS);
    }
  
  // Add team members again
    map(team_present, &(this_player())->team_join());
}
