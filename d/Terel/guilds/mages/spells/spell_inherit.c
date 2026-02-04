/* File         : /d/Terel/guilds/mages/spell/spell_inherit.c
  */
#pragma strict_types

#include "spells.h"
  
#include <filter_funs.h>
#include <composite.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>


public object *
spell_target_this_object(object caster, string str)
{
    return ({ this_object() });
}

public object *
spell_target_caster_environment(object caster, string str)
{
    return ({ environment(caster) });
}

public object *
spell_target_non_team_members(object caster, string str)
{
    object *livings;

    livings = FILTER_LIVE(all_inventory(environment(caster)));
    livings -= ({caster});
    livings -= caster->query_team_others();

    if (!sizeof(livings))
    {
	caster->catch_tell("There is no one here that is a valid target.\n");
	return ({});
    }

    return livings;
}


/* Function name: concentrate_msg
 * Description  : Generates the message for casting a spell
 * Arguments    : caster  - person casting the spell
 *                targets - things we are casting the spells on.
 *                args    - extra arguments.
 */
void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell("A polar storm begins to swirl as you focus your energy upon the elements.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) + " begins to gesture subtly, "
      + "waves of cold begin to radiate from " + POSSESSIVE(caster) + " body.\n");
}


