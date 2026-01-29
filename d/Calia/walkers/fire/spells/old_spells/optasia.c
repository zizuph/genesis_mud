
 /*
   * Night Vision Spell for the Firewalkers
   * by Jaacar
   * June 12th, 1997
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include FIRE_HEADER

public void optasia(object caster, object *targets, int *resist,
    int result);
public int create_spell_optasia(object caster, object *targets,
     string argument);

public object *
optasia_target_one_present_living(object caster, string str)
{
    object *oblist;

    if (!present("_optasia_potion_object_",caster))
    {
        caster->catch_tell("You are not feeling the effects of the "+
            "optasia potion.\n");
        return ({});
    }

    if (!strlen(str))
    {
        if (present(NVISION_OBJ, caster))
        {
            caster->catch_tell("You can already see in the dark!\n");
            return ({});
        }
        return ({ caster });
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == caster->query_real_name()))
	{
            if (present(NVISION_OBJ, caster))
            {
                caster->catch_tell("You can already see in the dark!\n");
                return ({});
            }
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
        
    if (present(NVISION_OBJ, oblist[0]))
    {
        caster->catch_tell("That person is already under the effects "+
            "of the Optasia spell!\n");
        return ({});
    }
    return oblist;
}

public void
create_spell_optasia(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(96);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE,40);
    set_spell_form(SS_PRAYER,40);
    set_spell_ingredients(({}));  // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object(OPTASIA_OBJ);
    return 0;
}

public void
optasia(object caster, object *targets, int *resist, int result)
{
    object target = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }

    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result)->move(targets[0]);

    targets[0]->catch_tell("Your eyes burn like fire, allowing you "+
            "to see in the darkness.\n");
    tell_room(environment(targets[0]),QCTNAME(targets[0])+"'s eyes "+
            "seem to erupt into small flames.\n",({ targets[0] }));
}
