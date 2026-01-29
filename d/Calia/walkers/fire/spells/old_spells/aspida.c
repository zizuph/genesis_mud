
  /*
   * Aspida (Flame Shield) Spell for the Firewalkers
   * by Jaacar
   * April 28th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/spell_config";
inherit "/d/Genesis/magic/targeting";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void aspida(object caster, object *targets, int *resist,
    int result);
public int create_spell_aspida(object caster, object *targets,
    string argument);

public int
create_spell_aspida(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(80);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE,40);
    set_spell_form(SS_PRAYER,40);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(aspida);
    set_spell_object(ASPIDA_ARM);
    return 0;
}

public object *
aspida_target_one_present_living(object caster, string str)
{
    object *oblist;

    if (!present("_aspida_potion_object_", caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "aspida potion!\n");
        return ({});
    }

    if (!strlen(str))
    {
        return ({ caster });
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == caster->query_real_name()))
	{
	    return ({ caster });
	}

	caster->catch_tell("There is no " + str + " here.\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }
        
    return oblist;
}

public void
aspida(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to "+
            "have no effect.\n");
        return;
    }

    if (targets[0] == caster)
    {
        if (present(ASPIDA_OBJ, caster))
        {
            caster->catch_tell("You are already protected!\n");
            return;
        }
 
        write("You are suddenly surrounded by a shimmering shield of "+
            "liquid fire.\n");
        tell_room(environment(caster), QCTNAME(caster) +" is suddenly "+
            "surrounded by a shimmering shield of liquid fire.\n",({caster}));
        make_spell_effect_object(query_spell_object(), caster, caster, 
            resist, result)->move(caster);
    }

    else
    {
        if (present(ASPIDA_OBJ, targets[0]))
        {
            caster->catch_tell("They are already protected!\n");
            return;
        }
        
        caster->catch_tell("You reach out and touch the shoulders of "+
            targets[0]->query_the_name(caster)+".  "+capitalize(TS_HE)+" is suddenly "+
            "surrounded by a shimmering shield of liquid fire.\n");
        tell_room(environment(caster),QCTNAME(caster)+" reaches out and "+
            "touches "+QTNAME(targets[0])+" on the shoulder.  "+
            capitalize(TS_HE)+" is suddenly surrounded by a shimmering shield of "+
            "liquid fire.\n",({caster,targets[0]}));
        targets[0]->catch_tell(caster->query_The_name(targets[0])+" reaches out and touches you "+
            "on the shoulder.  You are suddenly surrounded by a shimmering "+
            "shield of liquid fire.\n");
        make_spell_effect_object(query_spell_object(), caster, targets[0],
            resist, result)->move(targets[0]);
    }
}
