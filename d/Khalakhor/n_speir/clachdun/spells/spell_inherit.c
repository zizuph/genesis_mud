inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/spell_config";

#include <language.h>
#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

// Extra targeting functions.

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


// Other config stuff

void
default_conc_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You start to weave the pattern of your spell.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) +" starts to trace "+
      "an intricate pattern with "+HIS_HER(caster)+" hands as "+HE_SHE(caster)+
      " concentrates upon a spell.\n");
}

void
config_default_spell()
{
    set_spell_time(3);
    set_spell_mana_fail(0);
    set_spell_task(TASK_SIMPLE);
    set_spell_resist_task(TASK_IMPOSSIBLE);
    set_spell_stationary(0);
    set_spell_visual(0);
    set_spell_conc_message(default_conc_msg);
}

// Some extra resistance functions
public int
spell_resist_electricity(object caster, object target, int element, int difficulty)
{
    int res;

    res = max(0, min(100, 
	target->resolve_task(difficulty,
	  ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
	    SKILL_WEIGHT, 40, element,
	    SKILL_WEIGHT, 20, SS_SPELLCRAFT,
	    SKILL_WEIGHT, 20, TS_INT,
	    SKILL_WEIGHT, 40, TS_WIS,
	    SKILL_WEIGHT, 40, TS_DIS }))));

    res += combine_resistances(target, 
      ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_ELECTRICITY }));

    return min(res, 100);
}

public int
spell_resist_cold(object caster, object target, int element,
  int difficulty)
{
    int res;
    res = max(0, min(100,
	target->resolve_task(difficulty,
	  ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
	    SKILL_WEIGHT, 40, element,
	    SKILL_WEIGHT, 20, SS_SPELLCRAFT,
	    SKILL_WEIGHT, 20, TS_INT,
	    SKILL_WEIGHT, 20, TS_WIS,
	    SKILL_WEIGHT, 20, TS_DIS }))));

    res += combine_resistances(target, 
      ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_COLD }));

    return min(res, 100);
}

public int
query_spell_strength()
{
    return (gElement_skill + gForm_skill + gElement_needed + gForm_needed) / 4;
}
